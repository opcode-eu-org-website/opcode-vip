
/*
	Argumenty linii poleceń (w tym nazwa pod którą został uruchomiony program) przekazywne są do funkcji main jako dwa argumenty:
		1) liczba całkowita określająca ilość argumentów, typowo nazywany `argc`
		2) tablica napisów, typowo nazywany `argv`
*/

#include <stdio.h>
int main(int argc, char *argv[]) {
	printf("%d %s\n", argc, argv[0]);
	return 0;
}
