
// przy kompilacji konieczne jest dodanie:
//  -lrt -lpthread

#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <time.h>

#define BUF_SIZE 128

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "%s nazwa 1|2\n", argv[0]);
		return 1;
	}
	int retcode = 1;
	char runType = argv[2][0];
	
	// pamięć dzielona przez shm i mmap (więcej `man 7 shm_overview`)
	// można by także przez mmap i zwykły plik
	
	//  1) utworzenie zasobu (pliku) SHM
	//     jeżeli runType == '1' i zasób istnieje to wywołanie zakończy się błędem
	//                             ja jeżeli nie istnieje zostanie utworzony
	int shmFd = shm_open(
		argv[1], // nazwa zasobu
		O_RDWR|(runType == '1' ? O_CREAT|O_EXCL : 0), // flagi
		0770 // prawa dostępu
	);
	if (shmFd<0) {
		perror("Error in shm_open()");
		return 1;
	}
	
	//  2) ustalenie wielkości
	if (ftruncate(shmFd, BUF_SIZE)) {
		perror("Error in ftruncate()");
		goto END_1;
	}
	
	//  3) zamapowanie zasobu SHM w pamięci
	void *addr = mmap(0, BUF_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shmFd, 0);
	if (addr == MAP_FAILED) {
		perror("Error in mmap()");
		goto END_1;
	}
	
	// semafory POSIX (więcej `man 7 sem_overview`)
	
	//  1) utworzenie semafora
	//     jeżeli runType == '1' i semafor istnieje to wywołanie zakończy się błędem
	sem_t* sem = sem_open(
		argv[1], // nazwa zasobu
		O_RDWR|O_CREAT|(runType == '1' ? O_EXCL : 0), // flagi
		0770, // prawa dostępu
		1 // wartość semafora
	);
	
	if (sem == SEM_FAILED) {
		perror("sem_open");
		goto END_1;
	}
	
	int* c = (int*) addr;
	if (runType == '1') {
		*c = 0;
	}
	
	// próba wejścia w kod zabezpieczony semaforem
	if (sem_trywait(sem)) {
		if (errno == EAGAIN)
			puts("semafor nie wpuszcza ... trzeba spróbować później");
		else
			perror("Error in sem_trywait()");
	} else {
		// semafor został opuszczony ... jesteśmy w sekcji krytycznej
		*c = *c + 0x01;
		printf("c = 0x%x\n", *c);
		
		sleep(3); // śpimy, to nieładnie spać w sekcji krytycznej, ale to tylko demo ...
		
		// podniesienie semafora
		if (sem_post(sem))
			perror("Error in sem_post()");
	}
	
	sleep(5);
	
	// czekanie na możliwość wejścia w kod zabezpieczony semaforem z timeout'em
	struct timespec timeout;
	clock_gettime(CLOCK_REALTIME, &timeout);
	timeout.tv_sec+=10;
	if (sem_timedwait(sem, &timeout)) {
		if (errno == ETIMEDOUT)
			puts("timeout ... trzeba spróbować później");
		else
			perror("Error in sem_timedwait()");
	} else {
		// semafor został opuszczony ... jesteśmy w sekcji krytycznej
		*c = *c + 0x0100;
		printf("c = 0x%x\n", *c);
		
		sleep(5); // śpimy, to nieładnie spać w sekcji krytycznej, ale to tylko demo ...
		
		// podniesienie semafora
		if (sem_post(sem))
			perror("Error in sem_post()");
	}
	
	sleep(3);
	
	// czekamy do skutku na możliwość wejścia w sekcję krytyczną
	if (sem_wait(sem)) {
		perror("Error in sem_timedwait()");
	} else {
		// semafor został opuszczony ... jesteśmy w sekcji krytycznej
		*c = *c + 0x010000;
		printf("c = 0x%x\n", *c);
		
		sleep(5); // śpimy, to nieładnie spać w sekcji krytycznej, ale to tylko demo ...
		
		// podniesienie semafora
		if (sem_post(sem))
			perror("Error in sem_post()");
	}
	
	retcode = 0;
	
	// o ile w większości przypadków zwalnianie i zamykanie zasobów w momencie
	// kończenia programu nie ma znaczenia (zasoby są automatycznie odbierane przez
	// system - pamięć będzie zwolniona, pliki, gniazda sieciowe pozamykane, itd)
	// to w przypadku zasobów współdzielonych może mieć istotne znaczenie
	// np. jeżeli nie usuniemy zasobu SHM o danej nazwie nie będzie go można później
	// otworzyć gdy używamy flag O_CREAT|O_EXCL
	//
	// dlatego w powyższym kodzie w obsłudze błędów używamy goto do sekcji kończącej:
END_2:
	if (runType == '1') {
		// usunięcie semafora (stanie się niedostępny także dla innych procesów)
		sem_unlink(argv[1]);
	}
END_1:
	// odmapowanie zasobu z pamięci
	munmap(addr, BUF_SIZE);
	// zamknięcie zasobu SHM
	close(shmFd);
	if (runType == '1') {
		// usunięcie zasobu SHM (stanie się niedostępny także dla innych procesów)
		shm_unlink(argv[1]);
	}
	// w przypadku gdyby jednak program zakończył się bez wykonywania tego kodu
	// (np. na sutek kill -9) konieczne jest ręczne usunięcie plików z /dev/shm
}
