
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256

int main(int argc, char *argv[]) {
	int ret, sfd;
	char buf[BUF_SIZE];
	
	if (argc != 3) {
		fprintf(stderr, "%s dstHost dstPort\n", argv[0]);
		return 1;
	}
	
	// struktura zawierająca adres na który wysyłamy
	// użycie funkcji getaddrinfo pozwala na zapewnienie obsługi zarówno IPv4 jak i IPv6,
	// a także podawanie adresów w postaci numerycznej bądź przy użyciu nazw
	// alternatywnie można ręcznie przygotowywać struktury sockaddr_in / sockaddr_in6
	// z użyciem np. htons(), inet_aton(), ...
	struct addrinfo *dstAddrInfo;
	if((ret = getaddrinfo(argv[1], argv[2], NULL, &dstAddrInfo)) != 0) {
		fprintf(stderr, "Error in getaddrinfo(): %s\n", gai_strerror(ret));
		return 1;
	}
	
	// mogliśmy uzyskać kilka adresów, więc próbujemy używać kolejnych do skutku
	struct addrinfo *aiIter;
	for (aiIter = dstAddrInfo; aiIter != NULL; aiIter = aiIter->ai_next) {
		// utworzenie gniazda sieciowego ... SOCK_STREAM oznacza TCP
		sfd = socket(aiIter->ai_family, SOCK_STREAM, 0);
		if (sfd<0) {
			perror("Error in socket()");
			continue;
		}
		
		// łączymy z serwerem
		if (connect(sfd, aiIter->ai_addr, aiIter->ai_addrlen)) {
			perror("Error in connect()");
			close(sfd);
			sfd = -1;
			continue;
		}
		
		// udało się połączyć ... przerywamy sprawdzanie kolejnych adresów
		break;
	}
	freeaddrinfo(dstAddrInfo);
	if (sfd<0) {
		fprintf(stderr, "Can't connect\n");
		return 1;
	}
	
	const char* msg = "Ala ma Kota\n";
	if (send(sfd, msg, strlen(msg), 0) < 0) {
		// takie wywołanie send() jest równoważne wywołaniu write()
		perror("Error in send()");
		return 1;
	}
	
	// ustalamy limit czasu oczekiwania na dane 13s
	struct timeval timeOut;
	timeOut.tv_sec  = 13;
	timeOut.tv_usec = 0;
	
	// tworzymy zestaw deskryptorów dla funkcji select()
	// i umieszczamy w nim deskryptor gniazda sieciowego
	fd_set fdSet;
	FD_ZERO(&fdSet);
	FD_SET(sfd, &fdSet);
	
	// czekamy na dane w którymś z deskryptorów wchodzących
	// w skład zestawu lub timeout
	select(FD_SETSIZE, &fdSet, 0, 0, &timeOut);
	
	// select zmieni wartość fdSet i timeOut ...
	// będą one zawierały odpowiednio zbiór deskryptorów gotowych
	// do czytania i czas jaki pozostał do "wytimeoutowania"
	
	if (FD_ISSET (sfd, &fdSet)) {
		// jeżeli sfd jest w zbiorze gotowych do czytania to czytamy
		ret = read(sfd, buf, BUF_SIZE);
		if (ret < 0) {
			perror("Error in read()");
		} else if (ret == 0) {
			puts("connection close by peer");
		} else {
			buf[ret]='\0';
			printf("odebrano %d bajtów: %s\n", ret, buf);
		}
	} else {
		puts("timeout");
	}
	// w zależności od wymagań implementowanego protokołu można kontynuować
	// czekanie na kolejne dane z TCP i/lub jakiegoś innego wejścia (np. stdin),
	// można wysłać kolejne dane (żądanie) do serwera, itd ...
	//
	// w przypadku oczekiwania na dalsze dane (ponownego wywołania select) należy
	// pamiętać o ponownym ustawieniu fdSet i timeOut
	
	// zamkniecie gniazda
	close(sfd);
}
