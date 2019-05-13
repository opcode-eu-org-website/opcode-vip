
#include <iostream>
#include <stdint.h>

struct NazwaStruktury {
	// pola składowe
	int a;
	std::string d;
	
	// zmienna statyczna
	// wspólna dla wszystkich obiektów tej klasy
	static int x;
	
	// stała
	static const int y = 7;
	
	// pola binarne (jedno i trzy bitowe)
	uint8_t mA :1;
	uint8_t mB :3;
	
	// metody składowe
	void wypisz() {
		std::cout << " a=" << a << " d=" << d << "\n";
	}
	
	// deklaracja metody
	// definicja musi być podana gdzieś indziej
	int getSum(int b) ;
	
	/// metody statyczna
	static void info() {
		std::cout << "INFO\n";
	}
	
	// konstruktor i destruktor
	NazwaStruktury(int aa = 0) {
		std::cout << "konstruktor\n";
		a = aa;
		d = "abc ...";
	}
	~NazwaStruktury() {
		// potrzebny gdy klasa tworzy jakieś
		// obiekty które nalezy usuwać, itp
		std::cout << "destruktor\n";
	}
};

// definicja zmiennej statycznej z nadaniem jej wartości
// jest to niezbędne aby była ona widoczna ...
int NazwaStruktury::x = 13;

// wcześniej zdeklarowane metody
// możemy definiować także poza deklaracją klasy
int NazwaStruktury::getSum(int b) {
	return a + b;
}

int main() {
	// korzystanie ze struktur
	NazwaStruktury s;
	s.a = 45;
	s.wypisz();

	// korzystanie z metod statycznych
	NazwaStruktury::info();
	// a także poprzez obiekt danej klasy
	s.info();
}
