#include <stdio.h>
#include <inttypes.h>

int main() {
	// Język C wymaga określania typu zmiennej w momencie jej definiowania.
	
	// liczba całkowita ze znakiem
	int     liczbaA = -34;
	// liczba rzeczywista (pojedynczej precyzji)
	float   liczbaB = 673.1;
	// 8 bitowa liczba całkowita bez znaku, wymaga pliku nagłówkowego inttypes.h
	uint8_t liczbaC = 0xf3;
	
	// zmienna napisowa "C NULL-end string"
	char* napisA = "q we";
	
	printf("%d %x %d %.2f %s\n", liczbaC, liczbaC, liczbaA, liczbaB, napisA);
}
