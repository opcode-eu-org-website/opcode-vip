
#include <stdio.h>
#include <setjmp.h> // potrzebne dla długich skoków

jmp_buf long_jump_buffer;
void jakas_funkcja();

int main() {
	int i, j, k;
	
	// instrukcja waunkowa if - else
	if (i<j) {
		puts("i<j");
	} else if (j<k) {
		puts("i>=j AND j<k");
	} else {
		puts("i>=j AND j>=k");
	}
	
	// podstawowe operatory logiczne
	if (i<j || j<k)
		puts("i<j OR j<k");
	// innymi operatorami logicznymi są && (AND), ! (NOT)
	
	// operator warunkowy `warunek ? wartosc_gdy_prawda : wartosc_gdy_falsz`
	// gdzie zarówno `wartosc_gdy_prawda`, jak i `wartosc_gdy_falsz`,
	// mogą być wartością jak też wyrażeniem obliczającym jakąś wartość
	// (wyrażeniem matematycznym, wywołaniem funkcji, itd.)
	int z = (i==j) ? 5 : (2*13);
	
	// pętla for
	for (i=2; i<=9; ++i) {
		if (i==3)
			continue; // pominięcie tego kroku pętli
		if (i==7)
			break; // wyjście z pętli
		printf(" a: %d\n", i);
	}
	
	// pętla while
	while (i>0) {
		printf(" b: %d\n", --i);
	}
	
	// pętla do - while
	do {
		printf(" c: %d\n", ++i);
	} while (i<2);
	
	// instrukcja wyboru switch
	switch(i) {
		case 1:
			puts("i==1");
			break;
		default:
			puts("i!=1");
			break;
	}
	
	//
	// Niskopoziomowe mechanizmy skoków
	//
	
	// Instrukcje `goto` i funkcje `setjmp`/`longjmp` służą do bezpośredniego
	// zarządzania przepływem sterowania w programie, ale zazwyczaj unika się
	// tych mechanizmów, ponieważ mogą zmniejszać czytelność kodu.
	
	goto ETYKIETA;
	puts("to się nigdy nie wykona");
	puts("bo wcześniej robimy bezwarunkowe goto");
	
	ETYKIETA:
	puts("a to się wykona");
	
	// Najczęstszym przypadkiem użycia `goto` jest obsługa błędów w złożonych funkcjach
	// (tzw. "cleanup" na końcu funkcji). Skok `goto` do kodu wykonujące sprzątanie
	// i wyjście z funkcji używany jest zamiast return
	// w warunkach sprawdzających wystąpienie błędu.
	
	// Długi skok realizowany przez funkcje `setjmp` i `longjmp` pozwala na wykonywanie
	// skoków pomiędzy różnymi funkcjami. 
	// Funkcja `setjmp` zapisuje kontekst programu (m.in. stan stosu) i zwraca zero,
	// a `longjmp` pozwala do niego wrócić (w tym przypadku `setjmp` zwróci wartość
	// określoną w argumencie `longjmp`).
	
	int x = setjmp(long_jump_buffer);
	if (x == 0) { // setjump zapisało kontekst programu
		jakas_funkcja();  // wywołanie funkcji
	} else { // wróciliśmy do miejsca wywołania `setjump` na skutek wywołania `longjmp`
		printf("Powrót z longjmp, longjmp zostało wywołane z argumentem = %d\n", x);
	}
}

void jakas_funkcja() {
	longjmp(long_jump_buffer, 3);  // skok z powrotem do miejsca wywołania setjmp
	puts("to się nigdy nie wykona");
}
