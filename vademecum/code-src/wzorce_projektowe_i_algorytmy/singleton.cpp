
#include <iostream>

class Singleton {
private:
	// konstruktor, konstruktor kopiujący oraz operator
	// przypisania są prywatne aby uniemożliwić tworzenie
	// lub kopiowanie obiektów tej klasy z zewnątrz
	Singleton();
	Singleton(const Singleton&) {}
	Singleton& operator=(const Singleton&);
	
	// destruktor też prywatny ... dla zabezpieczenia przed
	// możliwością zrobienia delete na uzyskanym wskaźniku
	~Singleton() {}
	
	// klasa zawiera prywatny statyczny wskaźnik na siebie
	// (na swoją jedyną instancję)
	static Singleton* objPtr;
	
public:
	// a także metodę służącą pobraniu tego wskaźnika
	// (i utworzeniu obiektu gdy nie istnieje)
	static Singleton* getPtr() {
		// alternatywnie zamiast wskaźnika można użyć
		// statycznego obiektu tej klasy zadeklarowanego
		// wewnątrz tej funkcji
		if (!objPtr)
			objPtr = new Singleton();
		
		return objPtr;
	}
};

Singleton* Singleton::objPtr = 0;

Singleton::Singleton() {
	std::cout << "konstruktor Singleton\n";
}

int main() {
	Singleton* a = Singleton::getPtr();
	Singleton* b = Singleton::getPtr();
	std::cout << a << " == " << b << "\n";
}
