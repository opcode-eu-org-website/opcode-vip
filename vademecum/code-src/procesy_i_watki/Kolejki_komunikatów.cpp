
// przy kompilacji konieczne jest dodanie:
//  -lrt -lpthread

#include <stdio.h>
#include <mqueue.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void getMsg(union sigval sv) {
	puts("kolejka nie jest już pusta");
	// tu mógłby być realizowany odbiór wiadomości z kolejki
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "%s /nazwa 1|2\n", argv[0]);
		return 1;
	}
	char runType = argv[2][0];
	
	// kolejki wiadomosci POSIX (wiecej man 7 mq_overview)
	// kolejka może mieć zarówno wielu producentów jak i odbiorców
	// raz odebrana wiadomość znika z kolejki
	
	// otwarcie kolejki
	struct mq_attr atrybuty;
	atrybuty.mq_maxmsg=3;   // pojemność kolejki - 3 wiadomości
	atrybuty.mq_msgsize=20; // po 20 bajtów każda
	mqd_t msgQ = mq_open(
		argv[1], // nazwa zasobu
		O_RDWR|(runType == '1' ? O_CREAT|O_EXCL : 0), // flagi
		0770, // prawa dostępu
		&atrybuty
	);
	if (msgQ == (mqd_t) -1) {
		perror("Error in mq_open()");
		return -1;
	}
	
	char buf[20];
	unsigned priorytet;
	struct timespec timeout;
	clock_gettime(CLOCK_REALTIME, &timeout);
	timeout.tv_sec+=2;
	
	// odbieramy wiadomość z timeoutem ...
	// wiadomosci odbierane są w kolejności priorytetów, a następnie wysłania
	ssize_t size = mq_timedreceive(msgQ, buf, 20, &priorytet, &timeout);
	// mq_receive() - wersja bez timeoutu
	// mamy także możliwość odbioru bez timeoutu bądź zażądania powiadomienia
	// o wpisaniu pierwszej wiadomości do niepustej kolejki - mq_notify()
	if (size > 0){
		printf("odebrałem %d bajtów z priotytetem %d: %s\n", size, priorytet, buf);
	} else {
		if (errno == ETIMEDOUT)
			puts("timeout");
		else
			perror("Error in mq_timedreceive()");
	}
	
	// ustawienie powiadamiania o pojawieniu się wiadomości w niepustej kolejce
	struct sigevent sev;
	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = getMsg;
	sev.sigev_notify_attributes = NULL;
	if (mq_notify(msgQ, &sev) == -1) {
		perror("Error in mq_notify()");
	}
	
	// wysyłamy wiadomość do kolejki
	// funkcja ta zawiesi proces gdy nie ma miejsca w kolejce która nie jest
	// otwarta z O_NONBLOCK na czas określony przez timeout
	// mq_send() - wersja bez timeout'u
	snprintf(buf, 20, "info A od: %d", getpid());
	clock_gettime(CLOCK_REALTIME, &timeout);
	timeout.tv_sec+=2;
	if (mq_timedsend(msgQ, buf, strlen(buf), 9, &timeout))
		perror("Error in mq_timedsend()");
	printf("Wysłano: %s\n", buf);
	
	if (runType == '1') {
		snprintf(buf, 20, "info B od: %d", getpid());
		if (mq_send(msgQ, buf, strlen(buf), 9))
			perror("Error in mq_send()");
		printf("Wysłano: %s\n", buf);
		
		sleep(20);
		mq_unlink(argv[1]);
		// w przypadku gdyby program zakończył się bez wykonania mq_unlink()
		// (np. na sutek kill -9) konieczne jest ręczne usunięcie plików z /dev/mqueue
	}
}
