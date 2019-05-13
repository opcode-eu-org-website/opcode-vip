
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF1_SIZE 256
#define BUF2_SIZE 64

const char* getAddresInfo(
	struct sockaddr_storage *srcAddr, socklen_t srcAddrLen, char* buf, int bufLen
);

int main(int argc, char *argv[]) {
	char buf1[BUF1_SIZE], buf2[BUF2_SIZE];
	int  ret, pid;
	
	if (argc != 3 && argc != 4) {
		fprintf(stderr, "USAGE: %s dstHost dstPort [listenPort]\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	// struktura zawierająca adres na który wysyłamy
	// użycie funkcji getaddrinfo pozwala na zapewnienie obsługi zarówno IPv4 jak i IPv6,
	// a także podawanie adresów w postaci numerycznej bądź przy użyciu nazw
	// alternatywnie można ręcznie przygotowywać struktury sockaddr_in / sockaddr_in6
	// z użyciem np. htons(), inet_aton(), ...
	struct addrinfo *dstAddrInfo;
	if((ret = getaddrinfo(argv[1], argv[2], NULL, &dstAddrInfo)) != 0) {
		fprintf(stderr, "Error in getaddrinfo(): %s\n", gai_strerror(ret));
		return EXIT_FAILURE;
	}
	
	// tutaj mogliśmy uzyskać kilka adresów,
	// ale optymistycznie zakładamy że pierwszy będzie OK
	
	// utworzenie gniazda sieciowego ... SOCK_DGRAM oznacza UDP
	// (na gnieździe z SOCK_DGRAM standardowo nie będzie widać błędów ICMP
	//  związanych np. z niedostępnością docelowego hosta lub portu)
	int sfd = socket(dstAddrInfo->ai_family, SOCK_DGRAM, 0);
	if (sfd<0) {
		perror("Error in socket()");
		return EXIT_FAILURE;
	}
	
	if (argc == 4) {
		// jeżeli podane opcjonalne argumentu to określamy na jakim porcie słuchamy
		if (dstAddrInfo->ai_family == AF_INET6) {
			struct sockaddr_in6 listenAddr;
			listenAddr.sin6_family=AF_INET6;
			listenAddr.sin6_port=htons(atoi(argv[3]));
			// host to network short (porządek bajtów), są też dla long i network to host
			listenAddr.sin6_addr=in6addr_any;
			// in6addr_any oznacza że nasłuchujemy na każdym adresie IP danego hosta
			// (zamiast tego można określić konkretny adres)
			
			if(bind(sfd, (struct sockaddr *) &listenAddr, sizeof(struct sockaddr_in6))) {
				perror("Error in bind()");
				return EXIT_FAILURE;
			}
		} else if (dstAddrInfo->ai_family == AF_INET) {
			struct sockaddr_in listenAddr;
			listenAddr.sin_family=AF_INET;
			listenAddr.sin_port=htons(atoi(argv[3]));
			// host to network short (porządek bajtów), są też dla long i network to host
			listenAddr.sin_addr.s_addr=INADDR_ANY;
			// INADDR_ANY oznacza że nasłuchujemy na każdym adresie IP danego hosta
			// (zamiast tego można określić konkretny adres)
			
			if(bind(sfd, (struct sockaddr *) &listenAddr, sizeof(struct sockaddr_in))) {
				perror("Error in bind()");
				return EXIT_FAILURE;
			}
		}
		// określenie tego wraz z uruchomieniem recvfrom() pozwala na oczekiwanie na
		// pakiety UDP na wskazanym adresie i porcie, gdyby w ramach obsługi odebranej
		// wiadomości odsyłana byłaby odpowiedź do nadawcy to byłby to "serwer UDP"
	}
	
	// aby móc niezależnie wysyłać i odbierać rozgałęziamy proces
	// alternatywnie można użyć select() do czekania na dane z sieci lub standardowego wejścia
	switch (pid = fork()) {
		case -1: {
			// funkcja zwróciła -1 co oznacza błąd
			perror("Error in fork");
			return 1;
		}
		case 0: {
			// potomek odbiera odpowiedzi w nieskończonej pętli
			// zostanie zakończony sygnałem od rodzica
			
			while(1) {
				// struktura do której zapisany zostanie adres nadawcy
				struct sockaddr_storage srcAddr;
				socklen_t srcAddrLen = sizeof(struct sockaddr_storage);
				// informację tą można wykorzystać do odsyłania odpowiedzi do nadawcy
				
				// odbiór wiadomości ... blokuje do momentu otrzymania wiadomości
				ret = recvfrom(
					sfd, buf1, BUF1_SIZE, 0, (struct sockaddr *) &srcAddr, &srcAddrLen
				);
				
				// wypisanie wiadomości z informacją o nadawcy
				buf1[ret] = '\0';
				printf("odebrano %d bajtów od %s: %s\n",
					ret, getAddresInfo(&srcAddr, srcAddrLen, buf2, BUF2_SIZE), buf1
				);
			}
		}
		default: {
			// rodzic wysyła wiadomości
			while (fgets( buf1, BUF1_SIZE, stdin )) {
				ret = sendto(
					sfd, buf1, strlen(buf1), 0,
					dstAddrInfo->ai_addr, dstAddrInfo->ai_addrlen
				);
				printf("wysłano: %d bajtów: %s\n", ret, buf1);
			}
			// kończymy potomka gdy skończyliśmy nadawanie
			kill(pid, SIGTERM);
			wait(0);
		}
	}
	
	// zamkniecie gniazda
	puts("KONIEC");
	freeaddrinfo(dstAddrInfo);
	close(sfd);
}

// konwersja adresów IPv4 i IPv6 wraz z numerem portu na napis
const char* getAddresInfo(
	struct sockaddr_storage *srcAddr, socklen_t srcAddrLen,
	char* buf, int bufLen
) {
	if (srcAddrLen > sizeof(struct sockaddr_storage))
		return NULL;
	
	const char* addrStr = NULL;
	uint16_t port;
	if (srcAddr->ss_family == AF_INET) {
		struct sockaddr_in* srcAddrPtr = (struct sockaddr_in*) srcAddr;
		addrStr = inet_ntop(AF_INET, &(srcAddrPtr->sin_addr), buf, bufLen);
		port = ntohs(srcAddrPtr->sin_port);
	} else if (srcAddr->ss_family == AF_INET6) {
		struct sockaddr_in6* srcAddrPtr = (struct sockaddr_in6*) srcAddr;
		addrStr = inet_ntop(AF_INET6, &(srcAddrPtr->sin6_addr), buf, bufLen);
		port = ntohs(srcAddrPtr->sin6_port);
	}
	
	if (addrStr) {
		int len = strlen(buf);
		snprintf(buf+len, bufLen-len, ":%d", port);
	}
	
	return addrStr;
}
