
#include <iostream>
#include <vector>

int main() {
	// klasyczna tablica
	int t[4] = {1, 8, 3, 2};
	std::cout << t[2] << " -> ";
	t[2] = 55;
	std::cout << t[2] << " = " << *(t+2) << "\n";
	
	// jest ona podobnie jak struktura ciągłym obszarem pamięci,
	// możliwe jest zatem traktowanie takiej tablicy jako struktury
	struct Struktura {
		int a, b, c, d;
	};
	
	Struktura *tt = (Struktura*)t;
	std::cout << tt->a << " " << tt->c << "\n";
	
	
	// dynamicznie alokowana tablica C++ STL
	std::vector<int> v(4);
	v[3] = 21;
	std::cout << v[3] << "\n";
}
