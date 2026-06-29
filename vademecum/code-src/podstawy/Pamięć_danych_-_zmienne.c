#include <stdio.h>

int main() {
	// liczba całkowita ze znakiem
	int     calkowita = -34;
	// liczba rzeczywista (pojedynczej precyzji)
	float   zmiennoprzecinkowa = 673.1357;
	// 8 bitowa liczba całkowita bez znaku
	uint8_t bajt = 0xf3;
	
	printf("%d %x %d %.2f\n", bajt, bajt, calkowita, zmiennoprzecinkowa);
	
	// zmienna napisowa "C NULL-end string"
	char* napisA = "q we";
	// zmienna napisowa typu "C++ string" (to nie skompiluje się w C)
	std::string napisB = "a bc";
}
