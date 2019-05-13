
#include <iostream>
#include <list>

int main() {
	std::list<int> l;
	
	// dodanie elementu na końcu
	l.push_back(17);
	l.push_back(13);
	l.push_back(3);
	l.push_back(27);
	l.push_back(21);
	// dodanie elementu na początku
	l.push_front(8);
	
	// wypisanie liczby elementów
	std::cout << "size=" << l.size()<< "\n";
	
	// wypisanie pierwszego i ostatniego elementu
	std::cout << "first=" << l.front() << " last=" << l.back() << "\n";
	
	// usuniecie ostatniego elementu
	l.pop_back();
	
	// posortowanie listy
	l.sort();
	
	// odwrócenie kolejności elementów
	l.reverse();
	
	// usuniecie pierwszego elementu
	l.pop_front();
	
	for (std::list<int>::iterator i = l.begin(); i != l.end(); ++i) {
		// wypisanie wszystkich elementów
		std::cout << *i << "\n";
		// możliwe jest także:
		//  - usuwanie elementu wskazanego przez iterator
		//  - wstawianie elementu przed wskazanym przez iterator
	}
}
