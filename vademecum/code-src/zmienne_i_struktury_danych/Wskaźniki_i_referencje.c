
#include <stdio.h>

void f1(int a) {
    a = 15;
}

void f2(int* a) { // * oznacza że argumentem będzie wskaźnik
    *a = 15;
}

int main() {
	// zmienna typu int i wskaźnik na zmienna typu int
	int zm = 13;
	int *wsk = NULL; // zmienna wskaźnikowa (na typ int)
	
	// przypisanie do zmiennej wskaźnikowej adresu zmiennej zm
	// pobranie adresu zmiennej przy pomocy operatora &
	wsk = &zm;
	printf("%p = %p\n", &zm, wsk);
	
	// odwołanie do zmiennej wskazywanej przez wskaźnik (wyłuskanie wartości)
	// przy pomocy operatora *
	printf("%d = %d\n", zm, *wsk);
	
	// modyfikacja wartości na która wskazuje wskaźnik
	*wsk = 17;
	printf("%d = %d\n", zm, *wsk);
	
	//
	// Wskaźniki i tablice
	//
	
	// Zmienna tablicowa w C to w istocie wskaźnik na pierwszy element tablicy.
	// Dostęp do elementów tablicy odbywa się w oparciu o obliczanie ich adresu
	// na podstawie zależności:
	//    AdresElementu = AdresPoczatkuTablicy + IndexElementu * RozmiarElementu
	// czyli t[x] jest równoważne *(t+x)
	
	int t[4] = {1, 8, 3, 2};
	int *tt = t; // brak operatora pobrania adresu - tablica jest już wskaźnikiem
	
	printf("t[2] = %d = %d\n", t[2], tt[2]);
	printf("t[2] = %d = %d\n", *(t + 2), *(tt + 2));
	
	// Operator `t[x]` działa tak samo dla tablicy jak i dla wskaźnika i jest w istocie
	// ładniejszym zapisem operacji `*(t+x)` na samym wskaźniku.
	
	// Dzięki przemienności dodawania można nawet zapisać go odwrotnie ...
	printf("t[2] = %d = %d\n", 2[t], 2[tt]);
	
	// Na wskaźnikach można wykonywać (niektóre) operacje arytmetyczne.
	// Ich działanie jest zależne od typu wskaźnika, tj. zwiększenie wskaźnika
	// o 1 zwiększa adres na który on wskazuje o tyle bajtów,
	// ile zajmuje zmienna której typu jest wskaźnik.
	
	printf("t[0] = %d (%p)\n", *tt, tt);
	++tt; // zwiększmay wskaźnik - teraz będzie to pierwszy element tablicy
	printf("t[1] = %d (%p)\n", *tt, tt);
	
	//
	// Wskaźniki i funkcje
	//
	
	// Argumenty do funkcji przekazywane są przez kopiowanie,
	// w związku z tym modyfikacja zmiennej będącej argumentem funkcji
	// wewnątrz tej funkcji nie będzie widoczna poza nią:
	f1 (zm);
	printf("%d (wypisze 17)\n", zm);
	
	// Jeżeli chcemy mieć możliwość modyfikacji zmiennej przekazywanej
	// przez argument możemy przekazać zmienną do funkcji przez wskaźnik:
	f2(&zm);
	printf("%d (wypisze 15)\n", zm);
	
	// Jak było widać przy omawianiu tablic na wskaźnikach można wykonywać
	// (niektóre) operacje arytmetyczne.
	// Ich działanie jest zależne od typu wskaźnika, tj. zwiększenie wskaźnika
	// o 1 zwiększa adres na który on wskazuje, o tyle bajtów,
	// ile zajmuje zmienna której typu jest wskaźnik.
	char a;
	int  b;
	char *wsk_a = &a;
	int  *wsk_b = &b;
	
	printf("char: %p %p\n", wsk_a, wsk_a+1);
	printf("int:  %p %p\n", wsk_b, wsk_b+1);
	
	// UWAGA: wskaźniki na funkcje oraz wskaźniki na struktury i ich składowe
	//        (dostępne w czystym C) zostały omówione w przykładzie C++
}
