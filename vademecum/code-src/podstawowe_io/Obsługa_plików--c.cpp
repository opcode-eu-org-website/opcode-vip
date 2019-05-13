
#include <stdio.h>

int main() {
	//
	// obsługa plików w stylu C
	//
	
	// otwieramy plik określony w pierwszym argumencie,
	// w trybie określonym w drugim argumencie:
	// r - odczyt, w - zapis, a - dopisywanie,
	// + - dwukierunkowy (używane po r, w albo a)
	FILE *plik = fopen("/tmp/plik1.txt", "w+");
	
	// zapisujemy do pliku
	fputs("Hello World !!!\n", plik);
	fprintf(plik, "%.3f\n", 13.13131);
	
	// jako że są to operacje buforowane to aby mieć
	// pewność że to jest już w pliku należy wykonać
	// fflush(), nie jest to konieczne gdy zamykamy
	// plik (wtedy wykonywane jest z automatu)
	fflush(plik);
	
	int poz = ftell(plik);
	printf("aktualna pozycja w pliku to %d\n", poz);
	
	// przewijamy do początku
	// jest to równoważne rewind(plik);
	fseek(plik, 0, SEEK_SET);
	
	// wczytywanie z pliku
	char napis[10];
	fgets(napis, 10, plik);
	// wczytany napis będzie miał 9 znaków + NULL-end
	
	puts(napis);
	
	// powrot do poprzedniej pozycji
	fseek(plik, poz, SEEK_SET);
	
	// operacje binarne - w ten sposób możemy zapisywać
	// i odczytywać całe bufory z pamięci, czyli także napisy
	// zapis do pliku
	double x = 731.54112, y = 12.2;
	fwrite(&x, 1, sizeof(double), plik);
	fflush(plik);
	
	// przesuniecie do pozycji na której zapisywaliśmy
	fseek(plik, poz, SEEK_SET);
	// i odczyt z pliku ...
	fread(&y, 1, sizeof(double), plik);
	
	printf("zapisano: %f, odczytano: %f\n", x, y);
	
	// są także funkcje read() i write() działające w oparciu o
	// numeryczny deskryptor pliku uzyskiwany np. z funkcji open()
	// a nie obiekt FILE uzyskiwany z fopen()
	
	fclose(plik);
}
