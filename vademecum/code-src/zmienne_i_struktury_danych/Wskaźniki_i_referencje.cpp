
#include <stdio.h>
#include <iostream>

void f1(int *b) {
	*b = 2 * *b;
}

void f2(int (*f)(const char *s)) {
	f("Uwolnić mrożone truskawki !!!");
}

struct kl {
	// pola składowe
	int a;
	
	int getSum(int b) {
		return a + b;
	}
};

int main() {
	// zmienna typu int i wskaźnik na zmienna typu int
	int  a = 5678;
	int *b = NULL;
	
	// pobranie adresu zmiennej do wskaźnika
	b = &a;
	std::cout << "a ma adres " << b << "\n";
	
	// modyfikacja wartości na która wskazuje wskaźnik
	*b = 3456;
	std::cout << a << " = " << *b << "\n";
	
	// referencja
	int &c = a;
	c = 6543;
	std::cout << a << " = " << c << "\n";
	
	// wskaźniki na obiekty
	std::pair<int,int>  p = std::make_pair(2, 5);
	std::pair<int,int> *q = &p;
	
	// dostęp do składowych poprzez wskaźnik na strukturę
	(*q).first = 7;
	q->second = 8;
	std::cout << p.first << " " << p.second << "\n";
	
	// wskaźnik na składową
	b = &(q->second);
	*b = 3;
	std::cout << p.first << " " << p.second << "\n";
	
	// przekazywanie wskaźnika do funkcji:
	// 1. (podobnie jak trzymanie wskaźników na obiekty,
	//     zamiast obiektów w listach itp) pozwala na
	//     przekazywanie większych obiektów bez ich kopiowania
	// 2. pozwala na modyfikowanie wartości argumentów:
	f1(b);
	std::cout << p.first << " " << p.second << "\n";
	
	// wskaźnik "fun" na funkcje przyjmującą
	// wskaźnik const char i zwracającą int
	int (*fun)(const char *s);
	// przypisanie adresu funkcji puts do zmiennej fun
	fun = &puts;
	// użycie wskaźnika na funkcję jako funkcji
	fun("aaa");
	
	// wskaźnik na funkcję może być przekazywany
	// do innych funkcji jako argument
	f2(fun);
	
	// wskaźniki a tablice
	// w C tablica to wskaźnik na pierwszy element
	// a t[x] jest równoważne *(t+x)
	short t[4] = { 11, 22, 33, 44 };
	short *tt = t;
	std::cout << "t[2] = " << t[2] << " = " << *(t + 2) << "\n";
	
	std::cout << "t[0] = " << *tt << " @ " << tt << "\n"; ++tt;
	std::cout << "t[1] = " << *tt << " @ " << tt << "\n";
	
	// wskaźnik na metodę składową jakiejś klasy
	// (z wyjątkiem metod statycznych)
	// wymaga określenia typu tej klasy,
	// gdyż jest on typem niejawnego argumentu jej metod
	int (kl::*fun2)(int) = &kl::getSum;
	
	// aby skorzystać trzeba mieć obiekt danej klasy
	// (lub wskaźnik do niego)
	kl o1;
	o1.a = 2;
	kl *o2 = &o1;
	std::cout << (o1.*fun2)(3) << " " << (o2->*fun2)(3) << "\n";
}
