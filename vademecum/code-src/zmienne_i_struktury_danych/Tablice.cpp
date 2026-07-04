
#include <iostream>
#include <vector>

int main() {
	// klasyczna tablica z C
	// wartości elementów może zainicjalizować od razu przy deklaracji tablicy:
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
	
	// dynamicznie alokowana tablica C++
	
	// C++ oficjalnie nie obsługuje tablic zmiennej długości w stylu C99 C++
	// jednak niektóre z kompilatorów dopuszczają użycie VLA w C++.
	
	// C++ posiada za to typ std:vector pozwalający na definiowanie tablic,
	// których rozmiar można łatwo (z punktu widzenia programisty, niekoniecznie
	// maszyny wykonującej ten kod) zmieniać nawet po utworzeniu tablicy:
	
	std::vector<int> v(4);
	v[3] = 21;
	std::cout << v[3] << "\n";
}
