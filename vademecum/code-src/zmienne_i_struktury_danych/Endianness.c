#include <inttypes.h>
#include <stdio.h>
int main() {
	// dane jako tablica liczb 16 bitowych
	uint16_t aa[4] = {0x1234, 0x5678, 0x9abc, 0xdeff};
	
	// wypisujemy ją
	printf("A0: %x %x %x %x\n", aa[0], aa[1], aa[2], aa[3]);
	// chyba nikogo nie zaskoczy wynik powyższego printf:  A0: 1234 5678 9abc deff
	
	// wypisujemy dwie pierwsze liczby rozłożone na części 8 bitowe (poszczególne bajty)
	printf("A1: %x %x %x %x\n", (aa[0] >> 8) & 0xff, aa[0] & 0xff, (aa[0] >> 8) & 0xff, aa[0] & 0xff);
	// efekt też jest oczywisty:  A1: 12 34 12 34
	
	// każemy na te same dane patrzeć jako na liczby 8 bitowe (poszczególne bajty)
	uint8_t* bb = (uint8_t*) aa;
	
	printf("B0: %x %x %x %x\n", bb[0], bb[1], bb[2], bb[3]);
	// czego się teraz spodziewamy?
	//  - wypisze nam tylko połowę oryginalnej tablicy
	//  - ale dokładny wynik zależy od architektury na której uruchamiamy program:
	//    * na little endian (np. x86) będzie to:  B0: 34 12 78 56
	//    * na big endian (np. sparc) będzie to (bardziej naturalne dla człowieka):  B0: 12 34 56 78
}
