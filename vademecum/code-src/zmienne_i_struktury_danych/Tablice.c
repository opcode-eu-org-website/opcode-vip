
#include <stdio.h>

int main() {
	int tablica[3]; // tablica 3 elementowa liczb całkowitych
	
	tablica[0] = 13; // do elementów tablicy odwołujemy się z użyciem [],
	                 // elementy tablicy indeksujemy od zera
	tablica[2] = 17;
	
	printf("%d %d\n", tablica[0], tablica[1]);
	// nie zainicializowane elementy (tak samo jak nie zainicjalizowane zmienne)
	// będą mieć przypadkową wartość (nie jest to jednak dobre źródło losowości)
}

void xxx(int n) {
	// Język C od wersji C99 pozwala na korzystanie z tablic zmiennej długości (*VLA*),
	// czyli tablic których rozmiar nie jest stałą czasu kompilowania a zmienną - np.:
	float vals[n];
	v[0] = 21;
	/* ... */
}
