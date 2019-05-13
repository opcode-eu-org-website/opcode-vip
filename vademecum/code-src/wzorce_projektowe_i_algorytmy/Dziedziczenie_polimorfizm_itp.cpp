
// klasa abstrakcyjna - definiująca interfejs dla jakiejś grupy obiektów
// fakt bycia klasą abstrakcyjną wynika z niezdefiniowanej metody wirtualnej
// z faktu tego wynika niemożność utworzenia obiektów będących bezpośrednimi
// instancjami takiej klasy
class Ksztalt {
public:
	virtual float objetosc() = 0;
	// użycie virtual wymusza wywoływanie metody z klasy potomnej
	// kiedy odwołujemy się przy użyciu klasy bazowej
};

// klasy dziedzicząca po klasie Ksztalt
class Kula : public Ksztalt {
	float promien;
public:
	Kula(float r) {
		promien = r;
	}
	float objetosc() {
		return 1.25 * 3.14 * promien * promien * promien;
	}
};
class Szescian : public Ksztalt {
	float bok;
public:
	Szescian(float a) {
		bok = a;
	}
	float objetosc() {
		return bok*bok*bok;
	}
};

struct Kolor {
	char r, g, b;
};

class Cena {
public:
	Cena(float c);
};

class Material {
};

// klasa dziedzicząca po kilku klasach bazowych
struct Opakowanie : public Ksztalt, public Kolor, public Cena {
	Ksztalt  *ksztalt;
	Material *material;
public:
	Opakowanie(Ksztalt *k, const Kolor& kolor, float c) :
		// wywołanie konstruktorów klasy bazowej
		// jawnego dla Cena i kopiującego dla Kolor
		Cena(c), Kolor(kolor)
	{
		// inicjalizacja zmiennej wskaźnikowej ksztalt
		// dzięki rozwiązaniu z zmienną przechowującą informację o kształcie
		// nie ma potrzeby tworzenia różnych klas Opakowanie dla różnych kształtów
		ksztalt = k;
		material = 0;
	}

	Opakowanie(Ksztalt *k, float c) :
		// wywołanie konstruktora klasy bazowej Cena
		// oraz inicjalizacja zmiennych ksztalt i material
		Cena(c), ksztalt(k), material(0)
	{
		// inicjalizacja pól odziedziczonych po strukturze Kolor
		r = 0x96; g = 0xFF; b = 0x03;
	}

	float objetosc() {
		return ksztalt->objetosc();
	}

	// jest to alternatywna w stosunku co do dziedziczenia
	// metoda rozszerzania interfejsu jakiejś klasy
	
	// dziedziczenie (w przypadku dziedziczenia public) dodaje metody
	// klasy bazowej bezpośrednio do interfejsu klasy dziedziczącej
	// natomiast to rozwiązanie pozwala na pobranie poszczególnych klas
	// opisujących złożony obiekt niezależnie i operowaniu na ich interfejsie
	Material* getMaterial() {
		return material;
	}

	void setMaterial(Material *m) {
		material = m;
	}
};
