
/*
C++ pozwala także na definiowanie i używanie lambd. Definicja taka składa
się z listy przechwytywanych zmiennych, listy argumentów i ciała funkcji.

Lista przechwytywania może określać przechwytywanie przez wartość lub przez referencję.

W pierwszym przypadku wartość zmiennej z miejsca utworzenia funkcji zostanie w niej "zamrożona",
czyli jej dalsze zmiany nie będą widoczne w wywołaniach lambdy.

W drugim przypadku lambda będzie widzieć zawsze aktualną wartość,
a zmiany tej zmiennej wewnątrz lambdy będą widoczne także na zewnątrz.

Lista argumentów i ciało funkcji działa jak w zwykłych funkcjach.
Lambda może zwracać lub może nie zwracać wartość z użyciem return.
*/

#include <iostream>
int main() {
	int x = 10, z = 3;
	
	// lambda bez argumentów i listy przechwytywania
	auto lambda_function1 = []() {
		std::cout << "Hello\n";
	};
	lambda_function1();
	
	// lambda z argumentami
	auto lambda_function2 = [](int y) {
		std::cout << "y = " << y << "\n";
	};
	lambda_function2(11);
	
	// lambda z listą przechwytywania (przez wartość)
	// x jest zamrożone jako 10
	auto lambda_function3 = [x](int y) { return x + y; };
	std::cout << lambda_function3(3) << "\n";
	x = 0;
	std::cout << lambda_function3(3) << "\n";
	
	// lambda z listą przechwytywania (przez referencje)
	// odwołujemy się do zewnętrznego x
	auto lambda_function4 = [&x](int y) { return x + y; };
	std::cout << lambda_function4(3) << "\n";
	x = 10;
	std::cout << lambda_function4(3) << "\n";
	
	// w listach przechwytywania można podać wiele zmiennych
	// można mieszać przechwytywanie przez wartość
	// i referencję w ramach jednej lambdy
	
	auto lambda_function5 = [&x, z](int y) { return z * x + y; };
	
	// w C++ lambda może korzystać tylko ze zmiennych określonych
	// w jej listach przechwytywania i argumentów, czyli:
	//   auto lambda_function6 = [](int y) { return x + y; };
	// nie będzie poprawne
}
