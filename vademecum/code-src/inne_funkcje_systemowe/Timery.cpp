
// przy kompilacji konieczne jest dodanie:
//  -lrt -lpthread

#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void onTimer(int sig) {
	puts("timer !!!");
	
	// drzemka 0.35s
	// do spania można wykorzystać usleep(), sleep() lub nanosleep()
	// usleep i sleep działają bardzo podobnie
	// (z tym że pierwszy przyjmuje czas w sekundach, a drugi w mikrosekundach)
	usleep(350000);
}

int main() {
	// obslugujemy sygnał SIGALRM
	signal(SIGALRM, &onTimer);
	
	// najprostrzy timer ...
	alarm(4); pause();
	
	
	// timery POSIX (wiecej man timer_settime)
	
	//  1) tworzymy timer
	timer_t timer;
	timer_create(CLOCK_REALTIME, NULL, &timer);
	// podanie wskaźnika na strukturę sigevent zamiast NULL pozwala na określenie
	// innego sygnału jaki ma wygenerować timer lub obsługę tak jak wątku
	// (więcej w `man 7 sigevent`)
	
	//  2) konfiguryujemy timer
	struct itimerspec tSpec;
	//     pierwsze wykonanie timera po 100ms
	tSpec.it_value.tv_sec=0;
	tSpec.it_value.tv_nsec=100000000;
	//     kolejne co 1s
	//     (jezeli it_interval będzie wyzerowane to timer wykona się tylko raz)
	tSpec.it_interval.tv_sec=1;
	tSpec.it_interval.tv_nsec=0;
	
	//  3) uruchamiamy timer
	//     drugim argumentem są flagi - flaga TIMER_ABSTIME pozwala na
	//     ustawienie timera na czas absolutny (a nie okres czasu)
	timer_settime(timer, 0, &tSpec, NULL);
	char i=0;
	do {
		struct itimerspec tRest;
		timer_gettime(timer, &tRest);
		printf("do timera pozostało: %dns\n", tRest.it_value.tv_nsec);
		pause(); // czekamy na timer
		printf("aktualna liczba utraconych tyknięć timera wynosi %d\n",
			timer_getoverrun(timer));
	} while(i++<3);
	// powyższa metoda zapewnia rozpoczynanie w równych odstępach czasu ...
	// w przypadku zastosowania sleep() należałoby obliczać czas przez który
	// wykonywał się kod i odejmować go od czasu który podajemy do sleep()
	
	
	// drzemka
	
	// nanosleep pozwala na określenie sekund i milisekund oraz zwraca czas
	// różnicę pomiędzy planowanym czasem spania a rzeczywistym czasem
	// od wejścia do powrotu z funkcji nanosleep() - uwzględniając np. czas
	// obsługi sygnału który przerwał działanie funkcji nanosleep()
	struct timespec drzemka, pobudka;
	drzemka.tv_sec=2;
	drzemka.tv_nsec=100000000;
	// chcemy spac 2.1s ale obudzi nas timer
	// to ile zesmy niedospali zostanie zapisane w pobudka
	if (nanosleep(&drzemka, &pobudka)<0 && errno == EINTR)
		printf("niedospalismy: %ds i %dns\n", pobudka.tv_sec, pobudka.tv_nsec);
	
	// usuniecie timera
	timer_delete(timer);
}
