// poniższe polecenie każe zastąpić w kodzie programu każde wystąpienie _NAPIS_
// poprzez "Hello World"
#define _NAPIS_ "Hello World"
// w podobny sposób możemy definiować pseudo funkcje
#define _SUMA_(a,b) (a + b)
// poprzedzenie argumentu # powoduje ujęcie go w ""
#define _WYPISZ_(a) printf(#a)
// ## powoduje sklejenie ...

// ze względu na kontrolę błędów na etapie kompilacji
// zaleca się ograniczanie #define (w powyższych zastosowaniach)
// na rzecz stałych i funkcji inline

// możemy też warunkować włączanie fragmentów kodu
#define PL

#ifdef PL
	// ten fragment wykona się tylko gdy zdefiniowana PL
	#undef _NAPIS_
	// oddefiniowalismy _NAPIS_
	#define _NAPIS_ "Witaj World"
	// i zdefiniowaliśmy go inaczej
#endif

#if 0
to jest trzeci rodzaj komentarza w C
#endif

#include <stdio.h>

int main() {
	printf("%s\n", _NAPIS_);
	printf("%d\n", _SUMA_(5,3));
	_WYPISZ_ (witaj świecie !!! \n);
}
