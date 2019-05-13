
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

// funkcje obsługi sygnału
void obslugaSygnalu(int sig) {
	printf("Otrzymałem sygnał numer: %i\n", sig);
}

void akcjaSygnalu(int sig, siginfo_t *info, void *context) {
	printf("Otrzymałem sygnał numer: %i z kodem %d i wartością %d od pid=%d\n",
		sig, info->si_code, info->si_value.sival_int, info->si_pid);
	// si_code określa powód wysłania sygnału
}

int main() {
	int sig, pid;
	
	pid = getpid();
	printf("Mój PID=%d\n", pid);
	
	// sygnały są asynchronicznym mechanizmem jednokierunkowej komunikacji
	// systemy POSIXowe oferują dwa rodzaje sygnałów - standardowe i czasu rzeczywistego
	// sygnały czasu rzeczywistego (w odróżnieniu od standardowych przekazujących jedynie
	// numer sygnału) zawierają także kod i wartość oraz są priorytetyzowane
	// (niższy numer => wyższy priorytet => dostarczany w pierwszej kolejności)
	
	// do zdefiniowania obsługi sygnału standardowego (do jego przechwycenia) służy funkcja:
	signal(SIGINT,  &obslugaSygnalu); // pojawia się m.in. w efekcie Ctrl+C
	signal(SIGTSTP, &obslugaSygnalu); // pojawia się m.in. w efekcie Ctrl+Z
	// oczywiście można definiować różne funkcje dla różnych sygnałów
	// zamiast wskaźnika do funkcji możemy podać także SIG_IGN albo SIG_DFL
	// co oznacza odpowiednio ignorowanie tego sygnału lub jego domyślną obsługę
	
	
	// możliwe jest też maskowanie sygnałów
	sigset_t sigSet;
	
	// inicjujemy maskę sygnałów na pustą, na pełną byłoby sigfillset()
	if (sigemptyset(&sigSet))
		perror("Error in sigemptyset()");
	
	// dodajemy sygnał do maski
	// można także usuwać - sigdelset() i sprawdzać czy jest obecny - sigismember()
	// zamaskowany SIGTERM jest domyślnym sygnałem wysyłanym przez kill
	if (sigaddset(&sigSet, SIGTERM))
		perror("Error in sigaddset()");
	
	// ustawiamy maskę sygnałów na przygotowaną
	if (sigprocmask(SIG_SETMASK, &sigSet, NULL))
		perror("Error in sigprocmask()");
	
	// sygnały nie obsługiwane i nie blokowane przez proces obsługiwane są w sposób domyślny
	// na ogół prowadząc do zakończenia procesu ... sygnałów SIGKILL (wysyłanego przez kill -9)
	// oraz SIGSTOP nie można przechwycić ani zamaskować
	
	
	// do zdefiniowania obsługi sygnału czasu rzeczywistego służy funkcja sigaction wraz z strukturą
	// sigaction opisującą obsługę (można tak definiować także obsługę standardowych sygnałów):
	struct sigaction rtSigAct;
	// funkcja obsługi (moża także podać SIG_IGN albo SIG_DFL)
	rtSigAct.sa_sigaction = &akcjaSygnalu;
	// flagi ... SA_SIGINFO oznacza funkcję przyjmującą 3 argumenty a nie 1 jak w signal()
	rtSigAct.sa_flags = SA_SIGINFO;
	// maska sygnałów blokowanych w trakcie obsługi sygnału ... blokujemy wszystko co się da
	sigfillset(&rtSigAct.sa_mask);
	// ustawienie obsługi
	sigaction(SIGRTMIN, &rtSigAct, NULL);
	
	// wysłanie sygnału czasu rzeczywistego
	// (funkcja pozwala też na wysyłanie standardowych sygnałów)
	sigqueue(pid, SIGRTMIN, (const union sigval)123);
	
	
	// oczekiwanie na sygnał:
	puts("Czekam na dowolny sygnał");
	pause();
	
	// dodajemy SIGINT do zbioru
	if (sigaddset(&sigSet, SIGINT))
		perror("Error in sigaddset()");
	
	puts  ("Czekam na sygnał z podanej maski");
	puts  (" inne będą obsługiwane ale funkcja nie zakończy się ...");
	printf(" aby kontynuować Ctrl+C lub kill %d\n", pid);
	if (sigwait(&sigSet, &sig))
		perror("Error in sigwait()");
	printf("Czekanie zakończone po otrzymaniu sygnału: %d\n", sig);
	
	puts  ("Śpię przez 10s ... dowolny sygnał przerwie");
	sleep(10); // jest też usleep() dla mikro sekund
	
	puts  ("Czekam przez 10.5s na sygnał z podanej maski");
	siginfo_t sigInfo;
	struct timespec timeOut;
	timeOut.tv_sec  = 10;
	timeOut.tv_nsec = 500000000;
	sig = sigtimedwait(&sigSet, &sigInfo, &timeOut);
	if (sig<0) {
		if (errno == EINTR)
			puts("otrzymałem inny sygnał");
		else if (errno == EINVAL)
			puts("timeout");
		else
			perror("Error in sigtimedwait()");
	} else {
		printf("Czekanie zakończone po otrzymaniu sygnału %d od pid=%d\n",
			sig, sigInfo.si_pid
		);
	}
	// jest też sigwaitinfo działająca jak sigtimedwait ale bez timeout'u
}
