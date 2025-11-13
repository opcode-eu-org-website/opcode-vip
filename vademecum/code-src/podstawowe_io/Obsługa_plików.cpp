
#include <iostream>
#include <fstream>

int main() {
	//
	// obsługa plików w stylu C++
	//
	
	// tworzymy strumień związany z plikiem
	std::fstream plik_w;
	// otwieramy plik w trybie dopisywania
	// ale pozwalającym na modyfikowanie obecnej treści
	// aby to działało musi być to strumień in/out
	plik_w.open(
		"/tmp/plik2.txt",
		std::fstream::ate|std::fstream::out|std::fstream::in
	);
	
	// tworzymy strumień (typu in) związany z plikiem ...
	std::ifstream plik_r;
	// otwieramy plik do czytania
	plik_r.open("/tmp/plik1.txt");
	
	// tryby możemy budować z następujących opcji:
	//  std::ios::in - odczyt (domyślna dla ifstream)
	//  std::ios::out - zapis (domyślna dla ofstream)
 	//  std::ios::ate - ustawie pozycji na koniec pliku
	//  std::ios::app - dopisywanie bez możliwości zmiany zawartości
	//  std::ios::trunc - nadpisuje plik
	
	std::cout << "Pozycja w pliku OUT: " << plik_w.tellp() << std::endl;
	std::cout << "Pozycja w pliku IN: " << plik_r.tellg() << std::endl;
	
	// pisanie i czytanie dokładnie jak dla cin cout ...
	plik_w << "Hello World !!!";
	
	// przesunięcie na 16 bajt bliku wejściowego
	plik_r.seekg(16);
	// i wczytanie czegoś
	double x;
	plik_r >> x;
	std::cout << "wczytano: " << x << "\n";
	
	// przesunięcie o 2 bajty do tyłu i wczytanie
	plik_r.seekg(-2, std::ios::cur);
	// inne tryby przesunięć to:
	//  ios::beg - od początku pliku (domyślny)
	//  ios::end - od końca pliku
	plik_r >> x;
	std::cout << "wczytano: " << x << "\n";
	
	plik_w.seekp(-3, std::ios::end);
	plik_w << 123 << "\n";
	
	// nma koniec zamykamy pliki
	plik_w.close();
	plik_r.close();
}
