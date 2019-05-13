
// przy kompilacji konieczne jest dodanie:
//  -lrt -lpthread

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

struct watekInfo {
	pthread_mutex_t* mut;
	pthread_cond_t*  cond;
	const char*      napis;
	int              licznik;
};

void wypisz1(struct watekInfo* wi) {
	int i, l = -99, ret;
	for(i=0; i<4; i++) {
		// próbujemy zablokować wejście na ten kawałek kodu
		// można czekać do skutku przy pomocy pthread_mutex_lock()
		if ((ret = pthread_mutex_trylock(wi->mut)) != 0) {
			fprintf(stderr,
				"Wątek: error in pthread_mutex_trylock(): %s\n",
				strerror(ret)
			);
		} else {
			wi->licznik += 2;
			l = wi->licznik;
			pthread_mutex_unlock(wi->mut);
		}
		
		printf("Wątek: %s %d\n", wi->napis, l);
		usleep(600000);
	}
	sleep(8);
	pthread_exit(0); // kończy działanie wątku
}

void wypisz2(struct watekInfo* wi) {
	int i;
	printf("To watek: %s\n", wi->napis);
	
	pthread_mutex_lock(wi->mut);
	for(wi->licznik=0; wi->licznik<10; wi->licznik++) {
		printf("."); fflush(stdout);
		if (wi->licznik==5)
			pthread_cond_signal(wi->cond);
		sleep(1);
	}
	pthread_mutex_unlock(wi->mut);
	
	// zabraniamy przerwania watku w trakcie ponizszego wypisywania
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	for(i=0; i<10; i++) {
		printf("."); fflush(stdout);
		sleep(1);
	}
	printf("\n");
	// a teraz już może być anulowywany
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	
	// ale od teraz tylko w wyznaczonych momentach
	// na funkcjach takich jak sleep, system, ...
	// czy tez pthread_testcancel()
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	
	sleep(50);
	
	puts("koniec wypisz2");
	pthread_exit(0);
}

int main() {
	int i, l, ret;
	
	// przygotowanie mutex'a
	pthread_mutexattr_t mutAttr;
	pthread_mutexattr_settype(&mutAttr, PTHREAD_MUTEX_ERRORCHECK);
	// możemy ustawić:
	// * PTHREAD_MUTEX_ERRORCHECK aby mechanizm reagował błędem na
	//   unlockowanie zalokowanego przez inny wątek mutexu itp,
	// * PTHREAD_MUTEX_RECURSIVE aby blokada nałożona przez wątek A
	//   nie obowiazywala watku A (umożliwia to korzystanie z
	//   mutexów w funkcjach rekurencyjnych)
	// * PTHREAD_MUTEX_NORMAL lub PTHREAD_MUTEX_DEFAULT
	// flagi te mogą się nieco różnić w zależności od stosowanej
	// biblioteki i użytych #define szczegółów należy szukać
	// w plikach features.h pthread.h oraz dokumentacji man
	
	pthread_mutexattr_setprotocol(&mutAttr, PTHREAD_PRIO_NONE);
	// poza nic nie zmieniającym PTHREAD_PRIO_NONE mamy także:
	// * PTHREAD_PRIO_INHERIT zabezpieczający wątki przed inwersją
	//   priorytetów (priorytet po wejściu do sekcji krytycznej
	//   jest podwyższany do najwyższego z priorytetów procesów
	//   czekających
	// * PTHREAD_PRIO_PROTECT zabezpieczający również przed
	//   zakleszczeniem dzięki podnoszeniu tego priorytetu powyżej
	//   najwyższego z priorytetów procesów czekających
	//
	// do zapobiegania inwersji priorytetów przydatne jest też:
	// pthread_mutexattr_setprioceiling();
	
	// inicjalizujemy mutex (dla domyślnych ustawień można podać
	// NULL jako drugi argument)
	pthread_mutex_t mut;
	pthread_mutex_init(&mut, &mutAttr);
	
	// przygotowanie danych dla wątku
	struct watekInfo wInfo;
	wInfo.napis = "Ala ma kota";
	wInfo.licznik = 10;
	wInfo.mut = &mut;
	
	// tworzymy nowy watek uruchomiając w nim funkcje wypisz1
	// i przekazując jako pierwszy argument tej funkcji wInfo
	pthread_t watek;
	if ((ret = pthread_create(
			&watek, 0, (void* (*)(void *))wypisz1, (void*)&wInfo )
		) != 0
	) {
		fprintf(stderr, "Error in pthread_create(): %s\n",
			strerror(ret));
		return 1;
	}
	
	for(i=0; i<7; i++) {
		pthread_mutex_lock(wInfo.mut);
		wInfo.licznik -= 1;
		printf("Program główny: %d\n", wInfo.licznik);
		pthread_mutex_unlock(wInfo.mut);
		sleep(1);
	}
	
#ifdef _GNU_SOURCE
	// pobranie atrybutu wątku
	// i sprawdzenie czy jest wątkiem procesu czy systemu
	pthread_attr_t atrybuty;
	if ((ret = pthread_getattr_np(watek, &atrybuty))) {
		fprintf(stderr, "Error in pthread_getattr_np(): %s\n",
			strerror(ret));
		return 1;
	}
	if ((ret = pthread_attr_getscope(&atrybuty, &i))) {
		fprintf(stderr, "Error in pthread_attr_getscope(): %s\n",
			strerror(ret));
		return 1;
	}
	if (i == PTHREAD_SCOPE_PROCESS) {
		puts("wątek procesu");
	} else if (i == PTHREAD_SCOPE_SYSTEM) {
		puts("wątek systemu ... będzie widoczny w ps -m:");
		system("ps -m");
	} else {
		puts("inny wątek :-o");
	}
#endif
	
	// możemy oczekiwać na zakończenie wątku poprzez wywołanie
	// w innym funkcji pthread_join()  umożliwia ona także
	// uzyskanie kodu z jakim zakończył się wątek
	printf("Program główny czeka na koniec wątku\n");
	if ((ret = pthread_join(watek, NULL))) {
		fprintf(stderr, "Error in pthread_join(): %s\n",
			strerror(ret));
		return 1;
	}
	printf("Wątek zakończył się\n");
	// jej wywołanie jest konieczne aby wątek po zakończeniu
	// był w całości usunięty, chyba że wątek został określony
	// jako taki do którego nie można się dołączyć przez wywołanie
	// pthread_detach() lub podanie przy tworzeniu flagi
	// PTHREAD_CREATE_DETACHED
	
	
	// przygotowujemy zmienną warunkową
	pthread_cond_t cond;
	pthread_cond_init(&cond, NULL);
	
	// aktualizujemy strukturę danych dla wątku
	wInfo.napis = "drugi";
	wInfo.licznik = 0;
	wInfo.cond = &cond;
	
	// tworzymy kolejny wątek
	if ((ret = pthread_create(
			&watek, 0, (void* (*)(void *))wypisz2, (void*)&wInfo )
		) != 0
	) {
		fprintf(stderr, "Error in pthread_create(): %s\n",
			strerror(ret));
		return 1;
	}
	
	// czekamy ...
	while (wInfo.licznik < 5)
		pthread_cond_wait(wInfo.cond, wInfo.mut);
	// pthread_cond_wait zwalnia tak na prawdę na chwile podany
	// do niego mutex a po odebraniu pthread_cond_signal na
	// dozorowanym przez niego warunku ponownie go zamyka
	printf(" jesteśmy za warunkiem "); fflush(stdout);
	
	sleep(7);
	
	printf(" zabijamy wątek ");
	// i go kończymy z zewnątrz
	// w zależności od ustawień wątku anulowanie wątku dzieje
	// się natychmiastowo albo w jednym z punktów anulowania
	// zobacz funkcje to ustawiające w wypisz2()
	pthread_cancel(watek);
	
	// wypada też odebrać jego kod powrotu
	pthread_join(watek, NULL);
	puts("a teraz watek już nie żyje ...");
	
	
	// usunięcie mutex'a
	pthread_mutex_destroy(wInfo.mut);
	
	// usunięcie zmiennej warunkowej
	pthread_cond_destroy(wInfo.cond);
}
