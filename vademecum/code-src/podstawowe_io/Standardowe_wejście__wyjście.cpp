
#include <iostream>
#include <limits>
#include <iomanip>

int main() {
	//
	// wyjście / wyjście w stylu C++
	//
	
	// standardowe wyjście i standardowe
	// wyjście błędu jako strumienie C++
	std::cout << "Hello C++ world\n";
	std::cerr << "Hello C++ world 2\n";
	
	// strumienie pozwalają na proste wypisywanie zmiennych,
	// ale jeżeli chcemy formatować wyjście to
	// pisania jest więcej niż w printf
	int d = 1363;
	std::cout << "d=" << d << " d/3=" << d/3.0 << "\n";
	std::cout << std::setprecision(3) << 1.2342;
	std::cout << " " << 23.567 << "\n";
	
	// wczytanie napisu z standardowego wejścia:
	char napis[10];
	std::cin.getline(napis, 10);
	if (std::cin.fail()) {
		// zapominamy o reszcie jeżeli była
		std::cin.clear();
		std::cin.ignore(
			std::numeric_limits<std::streamsize>::max(),
			'\n'
		);
	}
	
	// wczytanie liczby z standardowego wejścia:
	std::cin >> d;
	
	std::cout << "liczba to: " << d;
	std::cout << " napis to: \"" << napis << "\"\n"; 
}
