
#include <iostream>

int funA(int a) {
	a = a*2;
	return a;
}

int funB(int &a) {
	a = a*2;
	return a;
}

int main() {
	int a = 57, b = 23;
	std::cout << ++a << " " << ++b << "\n";
	// wypisze 58 24
	{
		int a = b;
		std::cout << ++a << " " << ++b << "\n";
		// wypisze 25 25
		// bo a z tego bloku (==24) przesłoniło wcześniejsza zmienną a (==58)
	}
	std::cout << ++a << " " << ++b << "\n";
	// wypisze 59 26
	// bo a z wcześniejszego bloku już nie istnieje i nie przesłania naszego a (==58)
	
	std::cout << funA(a) << " " << funB(b) << "\n";
	// wypisze wartości zwracane przez funkcje czyli 118 (59*2) i 52 (26*2)
	std::cout << a << " " << b << "\n";
	// wypisze aktualne wartości argumentu:
	//  a=59 bo przekazanie przez wartość i funkcja operowała na własnej kopii
	//  b=52 bo przekazane przez referencję i funkcja operowała na tej samej kopii
}
