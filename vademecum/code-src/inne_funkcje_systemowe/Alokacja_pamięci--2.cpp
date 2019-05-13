
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <inttypes.h>

struct Abc {
	std::string a;
	int b;
private:
	short c;
public:
	Abc() {
		puts("konstruktor ABC");
		c = 123;
	}
	~Abc() {
		puts("destruktor ABC");
	}
	void print() {
		printf("a: %s, b: %d, c:%d\n", a.c_str(), b, c);
	}
};

struct Xxx {
	Abc abc1;
	Abc abc2;
	int tab[9];
	int xx1;
	int xx2;
};

int main(int argc, char *argv[]) {
	int a[5], aa;
	
	// alokacja pamięci
	int *bb = (int*)malloc(sizeof(int));
	int *cc = new int;
	int *c = new int[20]; // tablica alokowana dynamicznie w stylu C++
	Abc *dd = new Abc;
	
	printf("na stosie:   %p %p %p %p\n", &argv, &argc, &aa, a);
	printf("poza stosem: %p %p %p %p\n", bb, cc, c, dd);
	
	// zwalnianie pamięci
	free(bb);
	delete cc;
	delete c;
	delete dd;
	
	
	// alokujemy większy obszar pamięci przy pomocy malloc'a
	char* x = (char*)malloc(1024);
	// jest też realloc() umożliwiający zmianę rozmiaru zaalokowanego obszaru
	
	// zerujemy zaalokowaną pamięć ... na ogół nie jest to potrzebne,
	// ale w tym przykładzie może się przydać
	memset(x, 0, 1024);
	// często przydatna jest też funkcja memcpy() kopiująca wskazany
	// fragment pamięci w inne miejsce
	
	// pamięć zaalokowaną z użyciem malloc'a możemy dzięki
	// artmetyce wskaźnikowej oraz rzutowaniu typów wskaźnikowych
	// interpretować w dowolny sposób ...
	Abc *d1, *d2;
	int *b1, *b2;
	d1 = (Abc*)x;
	d2 = (Abc*)(x) + 1;
	b1 = (int*)(x + 2 * sizeof(Abc));
	b2 = b1 + 10;
	
	printf("rozmiar Abc: %ld == %ld == %ld\n",
		sizeof(Abc), (uint64_t)d2-(uint64_t)d1, (uint64_t)b1-(uint64_t)d2
	);
	
	d1->b = 15;
	d1->print();
	// jak widać powstał obiekt typu Abc, ale nie wykonał się konstruktor ...
	// ani konstruktory składowych (jak std::string), więc wywołanie:
	//  d1->a = "aa bb cc";
	// może się nie udać (zakończyć się np. Segmentation fault)
	//
	// aby uniknąć związanych z tym problemów możemy skorzystać z wariantu
	// operatora new który utworzy obiekt w zaalokowanej pamięci:
	new(d2) Abc;
	d2->a = "aa bb cc";
	d2->print();
	
	for (aa=0; aa<10; ++aa)
		b1[aa] = aa + 16;
	*b2 = 136917;
	
	// możemy też na taki obszar pamięci (nawet już zapełniony)
	// patrzeć np. jak na strukturę
	Xxx* z = (Xxx*)x;
	printf("%d == %d  %d == %d  %d == %d\n",
		z->tab[2], b1[2], z->xx1, b1[9], z->xx2, *b2
	);
	
	free(x); // takie zwolnienie nie wywoła destruktorów dla d1 i d2
}
