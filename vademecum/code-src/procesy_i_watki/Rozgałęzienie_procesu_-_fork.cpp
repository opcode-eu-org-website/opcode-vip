
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

void getInput(int fd, int pid);

int main() {
	// najprostszą metodą uruchomienia innego programu jest funkcja system
	int retcode = system("ls -l");
	printf("Program uruchomiony przez system() zwrócił kod powrotu: %d\n",
		WEXITSTATUS(retcode)
	);
	
	// jeżeli chcemy odebrać standardowe wyjście
	// (albo zapisać standardowe wejście) można skorzystać z popen
	FILE* p = popen("uname -a", "r");
	puts("Proces wypisał na swój stdout:");
	char buf[256];
	size_t s;
	while ((s = fread(buf, sizeof(char), sizeof(buf), p))) {
		fwrite(buf, sizeof(char), s, stdout);
	}
	
	
	// tworzymy łącza nie nazwane - rury ...
	int toSys[2];
	if ( pipe(toSys) == -1 ) {
		perror("Error in pipe(toSys)");
		// perror wypisuje podany komunikat na stderr dodając do niego opis
		// błędu określonego przez errno, można też pobrać identyfikator błędu
		// lub jego opis - szczegóły w man 3 errno
		return 1;
	}
	// toSys[0] - odbiór z rury
	// toSys[1] - wysyłanie przez rurę
	
	int fromSys[2];
	if ( pipe(fromSys) == -1 ) {
		perror("Error in pipe(fromSys)");
		return 1;
	}
	
	// rozgałęziamy proces
	int pid;
	switch (pid = fork()) {
		case -1: {
			// funkcja zwróciła -1 co oznacza błąd
			perror("Error in fork");
			return 1;
		}
		
		case 0: {
			// funkcja zwróciła zero co oznacza że jesteśmy w procesie potomnym
			
			// podmieniamy stdin i stdout potomka na odpowiednie
			// koniec łącz nienazwanych
			dup2(toSys[0], 0);
			dup2(fromSys[1], 1);
			
			// zamykamy końce łącz nienazwanych (te które używamy są już dostępne
			// jako stdin, stdout, innych nie potrzebujemy)
			close(toSys[0]); close(toSys[1]);
			close(fromSys[0]); close(fromSys[1]);
			
			// zastępujemy się innym procesem (w tym wypadku gerp dopasowujący napisy
			// zawierające znak z zakresu A-C) - w taki sposób w jaki robi to system()
			execl("/bin/sh", "sh", "-c", "grep --line-buffered '[A-C]'", (char *) 0);
			
			// oczywiście zamiast wywoływania innego programu można tutaj użyć własnego
			// kodu pracującego równolegle z programem głównym
		}
		
		default: {
			// funkcja zwróciła coś innego od 0 i -1 oznacza to że jesteśmy w procesie
			// macierzystym i otrzymaliśmy pid naszego dziecka ...
			
			// zamykamy niepotrzebne konce rur
			close(toSys[0]); close(fromSys[1]);
			
			// rury możemy obsługiwać jak pliki
			// i w ten spsób obsługiwana jest końcówka do zapisu
			FILE *pout = fdopen(toSys[1], "w");
			fprintf(pout, "Ala ma kota\n");
			fprintf(pout, "Kot ma coś\n");
			fflush(pout);
			
			// można też je obsługiwać posługując się bezpośrednio deskryptorem
			// i tak obsługiwana jest rura do czytania
			// rurę do czytania ustawiamy w trybie nie blokującym
			fcntl(fromSys[0], F_SETFL, fcntl(fromSys[0], F_GETFL, 0) | O_NONBLOCK);
			
			// czytanie zostało wyniesione jest do osobnej funkcji getInput()
			// celem łatwiejszego jego powtarzania
			getInput(fromSys[0], pid);
			
			// potomek może potrzebować trochę czasu na przetworzenie danych
			sleep(1);
			getInput(fromSys[0], pid);
			
			// zamykamy nasz koniec rury do pisania
			// pozwoli to potomkowi czekającemu na input zakończyć się
			fclose(pout);
			
			// sprawdzamy czy jest jeszcze jakiś input
			// (konieczne np. gdy grep bez --line-buffered)
			sleep(1);
			getInput(fromSys[0], pid);
			
			// zamykamy rurę do czytania
			close(fromSys[0]);
			
			// czekamy na zakończenie potomka
			int ppid = wait(&retcode);
			printf("potomek o PID=%d zakończył się z kodem %d\n",
				ppid, WEXITSTATUS(retcode)
			);
		}
	}
}

void getInput(int fd, int pid) {
	char* buf[256];
	int len, gLen = 0;

	while ((len = read(fd, buf, 255)) > 0) {
		buf[len] = 0;
		gLen += len;
		printf("Odebrano od potomka %d:\n>>>>>\n%s\n<<<<<\n", pid, buf);
	}
	printf("Łącznie odebrano: %d\n", gLen);
}
