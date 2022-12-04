 
// Już w powyższych przykładach użycia list i map w C++
// wykorzystane były iteratory, pozwalające na
// pobieranie kolejnych wartości z tych kontenerów:

void wypiszListe1(std::list<int> l) {
    for (std::list<int>::iterator i = l.begin(); i != l.end(); ++i) {
        std::cout << *i << "\n";
    }
}

// Iterator zwracają niektóre z metod tych kontenerów,
// np. .begin() zwraca iterator na pierwszy element.
// Zwiększanie iteratora odbywa się z użyciem operatora ++

// Wyjście poza zakres (zwiększenie iteratora wskazującego na
// ostatni element kolekcji) nie powoduje rzucenia wyjątku,
// za to iterator przyjmuje specjalną wartość oznaczającą koniec.
// Iterator o tej wartości zwracany jest przez metodę .end()
// (lub \cpp{.rend()} przy iterowaniu w przeciwną stronę).

// Przy używaniu iteratorów w C++ wygodne jest korzystanie
// z typu auto. Typ ten zwalnia programistę z konieczności
// jawnego definiowania typu zmiennej do której przypisywana
// jest od razu jakaś wartość z określonym typem.
// Można napisać np. `auto x = 5;`, ale nie możemy napisać:
// `auto x; x = 5;`

void wypiszListe2(std::list<int> l) {
    for (auto i = l.begin(); i != l.end(); ++i) {
        std::cout << *i << "\n";
    }
}

// C++ udostępnia także inną składnię pętli for pozwalającą
// na iterowanie po wszystkich elementach kolekcji takich jak
// listy, mapy, itp. I upraszczającą powyższy zapis do postaci:

void wypiszListe3(std::list<int> l) {
    for (auto i : l) {
        std::cout << i << "\n";
    }
}

// Zamiast `auto i` można napisać `auto& i` aby otrzymać dostęp
// przez referencję (wtedy wykonanie przypisania wartości do i,
// np. `i = 0`, spowoduje modyfikację elementu listy).

// Warto zauważyć także, że w odróżnieniu od wcześniejszej pętli
// zmienna reprezentuje wyłuskany iterator (jest to wartość /
// referencja do wartości elementu a nie sam iterator).
