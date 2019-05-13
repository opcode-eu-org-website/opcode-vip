
#include <stdio.h>

#include <stdarg.h>
// potrzebne dla obsługi dowolnej ilości argumentów

// funkcja bezargumentowa niezwracająca wartości
void f1() {
	puts("ABC");
}

// funkcja dwuargumentowa zwracająca wartość
int f2(int a, int b) {
	return a*2.5 + b;
}

// funkcja z jednym argumentem obowiązkowym
// i jednym opcjonalnym
float f3(int a, int b=1) {
	puts("F3");
	return a*2.5 + b;
}

// funkcja z dwoma argumentami wymaganymi
// i dowolną ilością argumentów opcjonalnych
float f4(int a, int b, ...) {
	float ret;
	
	va_list vl;
	va_start(vl, b);
	
	// w tym miejscu potrzebujemy znać ilość
	// oraz typy argumentów
	for (int i=0; i<a; i++) {
		ret += b * va_arg(vl,double);
	}
	va_end(vl);

	return ret;
}

int main() {
	f1();
	
	int a = f2(3, 6);
	// zwracaną wartość można wykorzystać
	// (jak wyżej) lub zignorować:
	f3(0);
	
	float b = f4(2, 1, 2.8, 3.5);
	
	printf("%d %f\n", a , b);
}
