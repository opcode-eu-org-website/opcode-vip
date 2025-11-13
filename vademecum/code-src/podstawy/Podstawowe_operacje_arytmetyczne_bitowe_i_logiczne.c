
#include <stdio.h>

int main() {
	double a = 12.7, b = 3, c, d, e;
	int x = 5, y = 6, z;
	
	// dodawanie, mnożenie, odejmowanie zapisuje się
	// i działają one tak jak w normalnej matematyce:
	e = (a + b) * 4 - y;
	
	// dzielenie zależy od typów argumentów
	d = a / b; // będzie dzieleniem zmiennoprzecinkowym bo a i b są typu float
	c = x / y; // będzie dzieleniem całkowitym bo z i y są zmiennymi typu int
	b = (int)a / (int)b; // będzie dzieleniem całkowitym
	a = (double)x / (double)y; // będzie dzieleniem zmiennoprzecinkowym
	
	// reszta z dzielenia (tylko dla argumentów całkowitych)
	z = x % y;
	
	// wypisanie wyników
	printf("%d %f %f %f %f %f\n", z, e, d, c, b, a);
	
	// operacje logiczne:
	// ((a większe równe od 0) AND (b mniejsze od 2)) OR (z równe 5)
	z = (a>=0 && b<2) || z == 5;
	// negacja logiczna z
	x = !z;
	
	printf("%d %d\n", z, x);
	
	// operacje binarne:
	// bitowy OR 0x0f z 0x11 i przesunięcie wyniku o 1 w lewo
	x = (0x0f | 0x11) << 1;
	// bitowy XOR 0x0f z 0x11
	y = (0x0f ^ 0x11);
	// negacja bitowa wyniku bitowego AND 0xfff i 0x0f0
	z = ~(0xfff & 0x0f0);
	
	printf("%x %x %x\n", x, y, z);
	
	// uwaga: powyższy program może nie wykonywać obliczeń w czasie działania
	// ze względu na optymalizację i fakt iż wyniki wszystkich operacji
	// są znane w momencie kompilacji programu
}
