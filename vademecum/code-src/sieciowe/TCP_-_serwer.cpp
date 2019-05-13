
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define BUF_SIZE 256
#define QUERY_SIZE 3
#define MAX_CHILD  5

int childNum = 0;
void onChildEnd(int sig) {
	puts("odebrano sygnał o śmierci potomka");
	--childNum;
	waitpid(-1, NULL, WNOHANG);
}

int main(int argc, char *argv[]) {
	int res;
	char buf[BUF_SIZE];
	
	if (argc != 2) {
		fprintf(stderr, "USAGE: %s listenPort\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	// obsługa sygnału o zakończeniu potomka
	signal(SIGCHLD, &onChildEnd);
	
	// utworzenie gniazda sieciowego ... SOCK_STREAM oznacza TCP
	int sfd = socket(PF_INET6, SOCK_STREAM, 0);
	if (sfd<0) {
		perror("Error in socket()");
		return EXIT_FAILURE;
	}
	
	// ustawienie opcji gniazda ... IPV6_V6ONLY=0 umożliwia korzystanie z tego
	// samego socketu dla IPv4 i IPv6 (rozszerzenie Linux-owe - na niektórych
	// systemach nie jest możliwe dualne słuchanie przy pomocy socketu IPv6)
	int opt = 0;
    if (setsockopt(sfd, IPPROTO_IPV6, IPV6_V6ONLY, &opt, sizeof(opt)) < 0) {
		perror("setsockopt(IPV6_V6ONLY=0)");
		return EXIT_FAILURE;
	}
	
	// utworzenie struktury opisującej adres
	struct sockaddr_in6 serwer;
	serwer.sin6_family=AF_INET6;
	serwer.sin6_port=htons(atoi(argv[1]));
	// host to network short (porządek bajtów), są też dla long i network to host
	serwer.sin6_addr=in6addr_any;
	// in6addr_any oznacza że nasłuchujemy na każdym adresie IP danego hosta
	// (zamiast tego można określić konkretny adres)

	// przypisanie adresu ...
	if (bind(sfd, (struct sockaddr *) &serwer, sizeof(struct sockaddr_in6)) < 0) {
		perror("Error in bind()");
		return EXIT_FAILURE;
	}

	// określenie gniazda jako używanego do nasłuchiwania połączeń przychodzących
	if (listen(sfd, QUERY_SIZE) < 0) {
		perror("Error in listen()");
		return EXIT_FAILURE;
	}
	
	while(1) {
		// odebranie połączenia
		struct sockaddr_in6 from;
		socklen_t fromLen=sizeof(struct sockaddr_in6);
		int sfd2 = accept(sfd, (struct sockaddr *) &from, &fromLen);
		
		// weryfikacja ilości potomków
		if (childNum >= MAX_CHILD) {
			printf("za dużo potomków\n");
			// można tutaj także wysłać informacje o błędzie serwera do klienta
			close(sfd2);
			continue;
		}
		
		// aby móc obsługiwać wiele połączeń rozgałęziamy proces
		int pid = fork();
		if (pid == 0) {
			// proces potomny ... zajmuje się tylko nowym połączeniem,
			// a nie nasłuchaniem więc zamykamy sfd
			close(sfd);
			
			// konwersja adresu na postać napisową
			char fromStr[64];
			snprintf(fromStr, 64, "%s:%d",
				inet_ntop(AF_INET6, &(from.sin6_addr), buf, BUF_SIZE),
				ntohs(from.sin6_port)
			);
			
			// obsługa połączenia
			printf("połączenie od: %s\n", fromStr);
			FILE * net;
			net=fdopen(sfd2, "r+");
			// należałoby tutaj używać czekania z timeout'em ...
			// inaczej usługa jest podatna na ataki DoS
			while(fgets(buf, BUF_SIZE, net)) {
				printf("odebrano od %s: %s\n", fromStr, buf);
				fputs(buf, net);
			}
			fclose(net);
			printf("koniec połączenia od: %s\n", fromStr);
			
			// zakończenie połączenia i potomka
			close(sfd2);
			return 0;
		}
		
		if (pid == -1)
			perror("Error in fork()");
		
		++childNum;
		close(sfd2);
	}

	// zamkniecie gniazda
	close(sfd);
}
