#include<iostream>
/// generowanie wyjątków
void wyj(int i) {
	switch(i) { // rzucamy wyjątek w zależności od i
		case 0:
			throw "Ala ma kota";
		case 1:
			std::cout << "wypisze sie (0) ?" << std::endl;
			throw "Kot ma Ale";
		case 2:
			throw 13;
	}
	std::cout << "wypisze sie (1) ?" << std::endl;
}

int main() {
	for (int j=0; j<4; j++) {
		std::cout << std::endl << "j = " << j << std::endl;
		try {
			wyj(j);
			std::cout << "wypisze sie (2) ?" << std::endl;
			wyj(1);
		} catch (char const* opis) {
			std::cout << "WYJATEK: " << opis << std::endl;
		} catch (...) {
			std::cout << "inny wyjątek" << std::endl;
		}
		// aby zaoszczędzić jednego kopiowania należy przechwytywać wyjątek przez referencję
		// ale należy pamiętać iż ze względu na mechanizm działania wyjątków
		// wartość ta i tak będzie kopiowana
	}
}
