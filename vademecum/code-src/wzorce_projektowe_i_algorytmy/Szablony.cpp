 
// Szablon funkcji wypisującej na standardowe wyjście
// listę dowolnego typu. Wymagane jest tylko aby dla tego
// typu był zdefiniowany operator << z std::iostream.

template <typename T> void wypiszListe(std::list<T>& l) {
    for (auto i : l) {
        std::cout << i << "\n";
    }
}

// przykład użycia
void wypisz() {
	std::list<int> x={1, 3, 7, 2, 3};
	wypiszListe(x);
	
	std::list<float> z={2.7, 5.0, 3.1, 3.9};
	wypiszListe(z);
}
