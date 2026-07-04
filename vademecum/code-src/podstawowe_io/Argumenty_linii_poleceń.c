
/*
Jak zostało już wspomniane funkcja `main()` zwraca wartość całkowitą.
Jest to kod powrotu programu, który służy do informowania procesu wywołującego
nasz program o tym czy zakończył się on sukcesem czy porażką.

W przypadku sukcesu powinien zwrócić 0. Niezerowa wartość oznacza niepowodzenie
(można użyć różnych wartości do sygnalizowania różnego rodzaju niepowodzeń.
Na przykład polecenie grep inaczej sygnalizuje nie znalezienie podanego wzorca,
a inaczej brak pliku który miało przeszukać).

Argumenty linii poleceń (w tym nazwa pod którą został uruchomiony program)
przekazywane są do funkcji main jako dwa pierwsze argumenty:
	1) liczba całkowita określająca ilość argumentów, typowo nazywany `argc`
	2) tablica napisów o długości określonej w pierwszym argumencie,
	   typowo nazywany `argv`

Elementami tablicy przekazywanej jako drugi argument są kolejne słowa
(ciągi znaków oddzielane niezabezpieczonymi spacjami) składające się na linię polecenia
w wyniku którego został uruchomiony program (czyli nazwa polecenia, opcje i argumenty)
*/

#include <stdio.h>
int main(int argc, char *argv[]) {
	printf("Liczba elementów: %d\n", argc);
	
	// tablica otrzymana jako drugi argumnent zawsze ma co najmniej jeden element
	// nazwę lub ścieżkę której użyto do uruchomienia programu.
	printf("Moja nazwa: %s\n", argv[0]);
	
	for (int i=0; i<argc; ++i)
		printf("element %d to: %s\n", i, argv[i]);
	
	return argc - 2; // kod powrotu uzależniamy od ilości argumentów
}

/*
Przykład działania (linie zaczynające się od `$` są wprowadzonymi komendami, pozostałe linie to output uruchomionych poleceń):

$ ./a.out a b; echo "Kod powrotu $?"
element 0 to: ./a.out
element 1 to: a
element 2 to: b
Kod powrotu 1
$ ./a.out a; echo "Kod powrotu $?"
element 0 to: ./a.out
element 1 to: a
Kod powrotu 0
*/
