
#include <stdio.h>

int main() {
	//
	// wyjście / wyjście w stylu C
	//
	
	// wykorzystywane już wcześniej funkcje
	// puts i printf korzystają z stdout
	puts("Hello world");
	printf("0x%x == %d == %.3f\n", 13, 13, 13.0);
	
	// jeżeli chcemy korzystać z innego strumienia
	// należy użyć wariantu pozwalającego na podanie
	// pliku do którego ma się odbywać zapis:
	// stdout - standardowe wyjście
	// stderr - standardowe wyjście błędu
	fputs("Hello world 2", stderr);
	fprintf(stderr, "0x%x == %d == %.3f\n", 13, 13, 13.0);
	
	// wczytanie napisu z standardowego wejścia:
	char napis[10];
	fgets( napis, 10, stdin );
	// wczytany napis będzie miał 9 znaków + NULL-end
	
	// zapominamy o reszcie inputu jeżeli był dłuższy niż 9 znaków
	if (napis[8] !='\n') {
		int c;
		while((c = getchar()) != '\n' && c != EOF);
	}
	
	// wczytanie liczby z standardowego wejścia:
	int d;
	fscanf (stdin, "%i", &d);
	
	fprintf(stdout, "liczba: %d napis: \"%s\"\n", d, napis);
}
