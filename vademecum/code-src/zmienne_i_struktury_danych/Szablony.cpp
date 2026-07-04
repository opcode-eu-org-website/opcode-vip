
/*
C++ pozwala też definiować szablony funkcji oraz klas,
dzięki którym kompilator będzie mógł wytworzyć funkcje/klasy dla potrzebnych typów
w oparciu o ten szablon (zdefiniowany dla ogólnego typu).

Na przykład wcześniej używana funkcja wypisująca listy
zdefiniowana jest tylko dla list zawierających liczby całkowite.
Jednak takie funkcje dla dowolnych typów obsługiwanych przez cout-owy operator `<<`
(np. liczb zmiennoprzecinkowych, napisów, ...) będą wyglądały tak samo.
Dzięki mechanizmowi szablonów możemy napisać:
*/

template <typename T> void wypiszListe(std::list<T>& l) {
	for (auto i : l) {
		std::cout << i << "\n";
	}
}

// i następnie używać jej dla różnych typów list:

void listy_demo() {
	std::list<int> x={1, 3, 7, 2, 3};
	wypiszListe(x);
	
	std::list<float> z={2.7, 5.0, 3.1, 3.9};
	wypiszListe(z);
}

// także typ zwracany może być określony z użyciem szablonu

template <typename T> T wyrazenie(T a, T b) {
	// T jest parametrem szablonu (typem zastępczym) i będzie zastąpione typem argumentu
	return a + 2*b*a + 3*b;
}

// przykłady użycia:
int main () {
	listy_demo();
	
	int a = 5;
	double b = 7.1;
	
	// 1. argumenty są typu int i wynik jest typu int
	int x = wyrazenie(a, 13);
	
	// 2. argumenty są typu double i wynik jest typu double
	double y = wyrazenie(b, 1.3);
	
	// 3. argumenty są różnych typów (double i int),
	// jawnie wymuszamy działanie funkcji `wyrazenie` typu double (jako T),
	// wartość `a` będzie rzutowana z int na double, wynik jest typu double
	double z = wyrazenie<double>(a, 1.3);
	
	// oczywiście wynik szablonu funkcji (jak każdej innej funkcji)
	// może być przypisany także do istniejącej zmiennej
	b = wyrazenie(b, 1.3);
}
