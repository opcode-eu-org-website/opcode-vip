
// UWAGA: przykład ten jest kontynuacją przykładu z języka C

#include <stdio.h>
#include <iostream>


void f3(int& a) { // & oznacza że argument będzie pobrany jako referencja
    a = 13;
}

void ff(int (*f)(const char *s)) {
	f("Uwolnić mrożone truskawki !!!");
}

struct Struktura {
	int a;
	int b;
	
	int getSum(int c) {
		return a + c;
	}
};

int main() {
	int  x = 5678;
	Struktura obiekt = {2, 4};
	
	//
	// wskaźniki na obiekty i ich składowe
	// (identycznie będzie działało to w czystym C)
	//
	
	// wskaźnik na strukturę
	Struktura *wsk = &obiekt;
	
	// dostęp do składowych poprzez wskaźnik na strukturę
	(*wsk).a = 7;
	wsk->b = 8;
	// `x->y` jest skróconym, ładniejszym zapisem dla `(*x).y`
	std::cout << obiekt.a << " " << obiekt.b << "\n";
	
	// wskaźniki na składowe
	int *aa = &(wsk->a);
	int *bb = &(obiekt.b);
	*aa = 13;
	*bb = 17;
	std::cout << obiekt.a << " " << obiekt.b << "\n";
	
	
	//
	// referencja
	// (to nie występuje w C)
	//
	
	// Referencje są zasadniczo wskaźnikami, których używa się jak zwykłych zmiennych
	// (bez stosowania operatora `*` w celu operowania na wartości wskaźnika).
	// W odróżnieniu od wskaźników nie możemy bezpośrednio operować na wskazywanym
	// przez nią adresie (np. spowodować aby wskazywała na inną zmienną).

	int &y = x;
	y = 6543; // brak operatora odwołania się do wskazywanej wartości
	std::cout << x << " = " << y << "\n";
	
	// przekazując referncję do funkcji uzyskamy takie samo zachowanie
	// jak w przypadku wskaźnika - funkcja będzie mogła modyfikować wartość argumentu
	// (inny jest sposób zapisu - zarówno w definicji funkcji jak i jej wywołaniu)
	f3(y); // w wywołaniu funkcji pobierającej argument jako referencja
	             // podajemy po prostu zmienną na którą chcemy uzyskać referencję
	              // nie ma tu operatora pobrania adresu jak przy wskaźniku
	std::cout << y << "\n";
	
	//
	// wskaźniki na funkcje
	// (identycznie będzie działało to w czystym C)
	//
	
	// wskaźnik "fun" na funkcje przyjmującą
	// wskaźnik const char i zwracającą int
	int (*fun)(const char *s);
	// przypisanie adresu funkcji puts do zmiennej fun
	fun = &puts;
	// użycie wskaźnika na funkcję jako funkcji
	fun("aaa");
	
	// wskaźnik na funkcję może być przekazywany
	// do innych funkcji jako argument
	ff(fun);
	
	//
	// wskaźniki na metodę
	// (to nie występuje w C)
	//
	
	// wskaźnik na metodę składową jakiejś klasy (z wyjątkiem metod statycznych)
	// wymaga określenia typu tej klasy
	// (gdyż jest on typem niejawnego argumentu jej metod)
	int (Struktura::*fun2)(int) = &Struktura::getSum;
	
	// aby skorzystać trzeba mieć obiekt danej klasy (lub wskaźnik do niego)
	std::cout << (obiekt.*fun2)(2) << " + 1 = " << (wsk->*fun2)(3) << "\n";
}

// Z wskaźników lub referencji stanowiących argumenty funkcji korzysta się także
// aby uniknąć kopiowania dużych struktur,
// w tym przypadku dobrym zwyczajem jest dodanie `const`,
// aby funkcja nie mogła modyfikować tego na co wskazuje ten wskaźnik

void f4(const struct Struktura *s) {
	// s->a = 15; // to spowodowałoby błąd kompilacji w tym miejscu,
	              // z powodu const w linii wyżej
	std::cout << s->a << "\n";
}

// Podobnie często używa się wskaźników na duże obiekty przy umieszczaniu ich
// w różnych strukturach danych (jak tablice, listy, itp) aby uniknąć ich kopiowania
