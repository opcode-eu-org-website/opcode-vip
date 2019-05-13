
#include <stdio.h>
#include <iostream>

#include <string>
#include <string.h>
#include <bitset>
#include <regex>
#include <sstream>

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
	
	
	// napisy w stylu C++
	std::string xx(x);
	std::string y = "aa bb cc bb dd bb ee";
	
	// wypisanie długości napisu
	std::cout << xx.size() << "\n";
	// .size() to to samo co .length()
	
	// uzyskanie napisy w stylu C
	puts(xx.c_str());
	
	// wypisanie pod-napisu od 2 do końca
	std::cout << xx.substr(2) << "\n";
	std::cout << xx.substr(2, std::string::npos) << "\n";
	// i od 0 (początku)do 3
	std::cout << xx.substr(0, 3) << "\n";
	
	// wyszukiwanie pod-napisu "bb" w y od pozycji 5
	std::cout << y.find("bb", 5) << "\n";
	
	// porównywanie
	if (xx == "a")
		std::cout << "x == \"a\"\n";
	if (xx.compare(0, 1, "a") == 0)
		puts("pierwsze 1 znaków x to \"a\"");
	
	if ( std::regex_match(xx, std::regex(".*[dz].*")) )
		puts("x zawiera d lub z");
		// regex_match dopasowuje całość napisu do wyrażenia regularnego
		// dopasowanie częściowe wraz z opcjonalnym uzyskaniem
		// pasującej części umożliwia: std::regex_search()
	
	// modyfikowanie std::string
	xx = "Ala ma psa";
	// wstawianie - insert(pozycja, co)
	xx.insert(6, " kota i");
	std::cout << xx << std::endl;
	
	// zastępowanie - replace(pozycja, ile, czym);
	xx.replace(4, 2, "miała samochód", 0, 6);
	// mogłoby też być xx.replace(4, 2, "miała"); i parę innych wariantów ...
	std::cout << xx << std::endl;
	
	// usuwanie - erase(pozycja, ile);
	xx.erase(9, 1); // 9 zamiast 8 bo UTF-8 i ł ma dwa znaki
	std::cout << xx << std::endl;
	
	// zastępowanie z użyciem wyrażeń regularnych
	std::cout << std::regex_replace (y, std::regex("[bc]+"), "XX") << "\n";
	
	// zastępowanie z użyciem podstawienia
	// $2 zostanie zastąpione wartością drugie pod-wyrażenia,
	// czyli fragmentu ujętego w nawiasach
	std::cout << std::regex_replace (
		y, std::regex("([bc]+) ([bc]+)"), "X-$2-X"
	) << "\n";
	
	// konwersja liczb na napis w systemach:
	// dwójkowym, ósemkowym, dziesiętnym i szesnastkowym
	
	std::cout << std::bitset<8>(7) << " ";
	std::cout << std::oct << 0xf << " ";
	std::cout << std::dec << 010 << " ";
	std::cout << std::hex << 0b11 << "\n";
	
	// liczby podawane do wypisywania są w odpowiednio systemach:
	// dziesiętnym, szesnastkowym, ósemkowym i dwójkowym
	// wskazane jest to przez brak prefixu i prefixy "0x" "0" "0b"
	
	// alternatywnie w stylu printf, ale bez dwójkowego
	printf("0o%o %d 0x%x\n", 0xf, 010, 0b11);
	
	// wypisywanie znaków unicodu
	puts("\u21c4 = ⇄");
	
	// strumienie napisowe
	std::ostringstream zzz;
	zzz << xx << " cpp\n";
	zzz << 34.6 << " " << std::oct << 0xf << " ";
	
	// konwersja do std::string
	xx = zzz.str();
	
	std::cout << xx << "\n";
}
