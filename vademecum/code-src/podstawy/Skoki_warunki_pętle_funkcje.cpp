
#include <stdio.h>

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
	
	// pętla for
	for (i=2; i<=9; ++i) {
		if (i==3) {
			// pominięcie tego kroku pętli
			continue;
		}
		if (i==7) {
			// wyjście z pętli
			break;
		}
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
	
	goto ETYKIETA;
	puts("to się nigdy nie wykona");
	puts("bo wcześniej robimy bezwarunkowe goto");
	
	ETYKIETA:
	puts("a to się wykona");
}
