
// definicja szablonu
template <typename T> T wyrazenie(T a, T b) {
	// T jest parametrem szablonu (typem zastępczym) i będzie zastąpione typem argumentu
	return a + 2*b*a + 3*b;
}

// przykłady użycia:

// 1. argumenty są typu int i wynik jest typu int
int fun1(int a) { return wyrazenie(a, 13); }

// 2. argumenty są typu double i wynik jest typu double
double fun2(double a) { return wyrazenie(a, 1.3); }

// 3. argumenty są różnych typów (double i int),
// jawnie wymuszamy działanie funkcji `wyrazenie` typu double (jako T),
// wartość `a` będzie rzutowana z int na double, wynik jest typu double
double fun3(int a) { return wyrazenie<double>(a, 1.3); }
