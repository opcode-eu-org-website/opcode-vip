
/* 
Napisy w języku C są tablicami bajtów (tablicami typu `char`)
zakończonymi bajtem o wartości zero (NULL),
będącym znacznikiem końca napisu.

Pojedynczy znak reprezentowany jest poprzez jeden element tablicy
(dla znaków kodowanych jednobajtowo) lub grupę takich elementów
(dla znaków kodowanych wielobajtowo, np. polskich znaczków w UTF8).
*/

#include <stdio.h>
#include <string.h>

int main() {
	// napisy w stylu C
	// czyli tak naprawdę tablice bajtów (znaków)
	const char* x = "abcdefg";
	
	// wypisanie długości napisu
	printf("%d\n", strlen(x));
	
	// wypisanie pod-napisu od 2 do końca
	puts(x+2);
	
	// wyszukiwanie
	// pod-napisu "cd" w x od pozycji 1
	const char* cd = strstr(x+1, "cd");
	printf("%d\n", cd-x);
	
	// 3 znakowy pod-napis napisu x
	// rozpoczynający się od cd
	char buf[16];
	strncpy(buf, cd, 3);
	buf[3]=0; // NULL end
	puts(buf);
	
	// porównywanie
	if (strcmp(x, "a") == 0)
		puts("x == \"a\"");
	if (strncmp(x, "a", 1) == 0)
		puts("pierwsze 1 znaków x to \"a\"");
	
	/*
	W C pojedynczy znak napisu (czyli np. `char x = napis[i]` albo `char x = 'A';`)
	nie jest napisem – jest liczbą (zauważ różnicę między apostrofami i cudzysłowami).
	Można go wypisać z użyciem `printf()` jako wartość numeryczną poprzez `%d`
	lub jako znak poprzez `%c`:
	*/
	
	printf("%d <=> %c", 'A', 'A');
}
