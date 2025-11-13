
#include <iostream>
int main() {
	int x = 10;
	
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
	
	// w C++ lambda może korzystać tylko ze zmiennych określonych
	// w jej listach przechwytywania i argumentów, czyli:
	//   auto lambda_function5 = [](int y) { return x + y; };
	// nie będzie poprawne
}
