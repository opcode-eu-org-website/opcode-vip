
// program korzysta z mechanizmów systemów POSIX
// i może nie działać na niekompatybilnych platformach

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>
#include <stdio.h>

#define _MMAP_MODE_  MAP_PRIVATE // MAP_SHARED

// MAP_PRIVATE powoduje bez widoczności zmian w mapowanym pliku dla innych procesów
// MAP_SHARED  pozwala współdzielić zamapowany obszar z innymi procesami,
//             jest wymagane aby móc zmodyfikować plik z użyciem msync()

int main() {
	const char* fname = "/tmp/aaa.txt";
	int fsize;

	// pobieramy rozmiar pliku
	struct stat st;
	if (stat(fname, &st)) {
		if (errno == ENOENT) {
			printf("plik \"%s\" nie istnieje\n", fname);
			fsize = 0;
		} else {
			fprintf(stderr, "Error in stat(): %s\n", strerror(errno));
			// powyższe zadziała jak perror()
			return -1;
		}
	} else {
		fsize = st.st_size;
	}

	// otwieramy plik w trybie zapis-odczyt uzyskując deskryptor
	// (jeżeli plik nie istnieje zostanie utworzony z prawami 600)
	int fd = open(fname, O_RDWR|O_CREAT, (mode_t)0600);
	
	int bufSize = fsize + 20;
	
	// jeżeli chcemy operować na większym buforze niż rozmiar pliku musimy powiększyć plik
	if (ftruncate(fd, bufSize))
		perror("Error in ftruncate()");
	// operacja ta nie ma wpływu na zajmowane miejsce na dysku:
	//   int fd = open("/tmp/x", O_RDWR|O_CREAT); ftruncate(fd, 100000000); close(fd);
	//   utworzy plik /tmp/x którego rozmiar wg `ls` będzie 98MB a wg `du` będzie 0
	// alternatywnie można:
	//   lseek(fd, bufSize-1, SEEK_SET); write(fd, "", 1); lseek(fd, 0, SEEK_SET)
	
	// mapujemy plik do pamięci ... w trybie odczytu i zapisu
	char *buf = (char*)mmap(NULL, bufSize, PROT_READ | PROT_WRITE, _MMAP_MODE_, fd, 0);
	if (buf == MAP_FAILED) {
		perror("Error in mmap()");
		return -1;
	}

	buf[fsize]=0;
	printf("Długość pliku: %d\n", fsize);
	printf("Zawartość pliku: %s\n", buf);

	// modyfikujemy przedostatni bajt w pliku
	// (jeżeli trafimy na fragment wielo-bajtowego znaku to go popsujemy)
	if (fsize > 2)
		buf[fsize - 2]='X';

	fsize += snprintf(buf+fsize, bufSize-fsize, "Ala ma kota\n\n");
	fsize += snprintf(buf+fsize, bufSize-fsize, "Kot ma Alę\n\n");
	fsize += snprintf(buf+fsize, bufSize-fsize, "czyżby ...\n\n");
	
	// do pliku chcemy zapisać "fsize" bajtów z "buf", czyli: buf[0] ... buf[fsize-1]
	// nie chcemy zapisać kończącego napis znaku NULL (dodawanego przez snprintf),
	// jeżeli nie doszło do przepełnienia bufora nie jest on wliczany w długość "fsize"
	// i znajduje się w buf[fsize], zatem nie ma konieczności jawnego pomijania go
	//
	// jeżeli natomiast doszło do przepełnienia bufora jest on ostatnim znakiem w buforze,
	// czyli buf[bufSize-1] ... zatem aby go pominąć należy ustawić fsize = bufSize -1
	if (fsize >= bufSize) {
		fprintf(stderr, "Error: przepełnienie bufora\n");
		fsize = bufSize -1;
	}
	printf("Nowa długość pliku: %d\n", fsize);
	printf("Nowa zawartość pliku: %s\n", buf);
	
	// ustawiamy prawidłowy rozmiar pliku
	if (ftruncate(fd, fsize))
		perror("Error in ftruncate()");
	
#if _MMAP_MODE_ == MAP_SHARED
	// synchronizujemy zawartość bufora pamięci do pliku
	if (msync(buf, fsize, MS_SYNC))
		perror("Error in msync()");
#else
	// zapisujemy zmiany do pliku
	if (write(fd, buf, fsize) < 0)
		perror("Error in write()");
#endif
	
	// odmapowanie pliku z pamięci
	if (munmap(buf, fsize))
		perror("Error in munmap()");
	
	// zamknięcie pliku
	close(fd);
}
