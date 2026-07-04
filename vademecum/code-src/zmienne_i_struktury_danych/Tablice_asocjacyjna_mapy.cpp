
#include <iostream>
#include <map>

int main() {
	std::map<std::string, int> m;
	
	m["a"] = 6;
	m["cd"] = 9;
	std::cout << m["a"] << " " << m["ab"] << "\n";
	
	// wyszukanie elementu po kluczu
	std::map<std::string, int>::iterator iter = m.find("cd");
	// sprawdzenie czy istnieje
	if (iter != m.end()) {
		// wypisanie pary - klucz wartość
		std::cout << iter->first << " => " << iter->second << "\n";
		// usunięcie elementu
		m.erase(iter);
	}
	
	m["a"] = 45;
	
	// wypisanie całej mapy
	for (iter = m.begin(); iter != m.end(); ++iter)
		std::cout << iter->first << " => " << iter->second << "\n";
	// jak widać mapa jest wewnętrznie posortowana
	
	// Mapa `std::map` nie zachowuje kolejności wkładania elementów,
	// natomiast jest zawsze posortowana. C++ oferuje też inne rodzaje map, np.:
	// * nie posortowaną `std::unordered_map`,
	// * nie wymagającą unikalności klucza `std::multimap`.
}
