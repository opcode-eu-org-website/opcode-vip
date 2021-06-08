
/*  PLIK: py_api.cpp      kompilacja:
	g++ --std=c++11 -shared -fPIC -I/usr/include/python3.7m/ py_api.cpp \
		-o MyPyAPI.so -lpython3.7m -lboost_python37
	uwaga: - kolejność argumentów może być istotna
	       - plik wynikowy powinien mieć taką samą nazwę jak moduł
	         zadeklarowany przy pomocy BOOST_PYTHON_MODULE()
*/

#include <iostream>
#include <string>
#include <list>

std::string f1(int a) {
	for (int i=0; i<a; ++i)
		std::cout << "Ala ma kota\n";
	return "Kot ma Alę";
}

struct K1 {
		int a;
		static K1* obj;
		int f1(int b) { return a + b; }
		static K1* get() { return obj; }
};

void f2(K1& k, int n) {
	std::cout << "run f2(): " << k.f1(2*n) << "\n";
	k.a += 1;
}

K1* K1::obj = NULL;

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(MyPyAPI) {
	boost::python::def("f1", f1);
	
	boost::python::class_<K1>("Klasa")
		.def_readwrite("a", &K1::a)
		.def("f1", &K1::f1)
		// w pythonie w odróżnieniu od C++ referencja do klasy jest jawnym
		// argumentem metod nie statycznych zatem f2 które przyjmuje jako
		// pierwszy argument referencję do obiektu klasy K1 możemy użyć
		// jako metody klasy pythonowej
		.def("f2", f2)
		
		// typo z funkcji do pythona zwracana jest wartość zmiennej (a nie
		// referencja do zmiennej C++) jednak dla funkcji zwracających
		// wskaźnik lub referencję na ogół chcemy aby zwracana była właśnie
		// referencja do istniejącej zmiennej C++
		.def("get", &K1::get,
			 boost::python::return_value_policy<
				boost::python::reference_existing_object
			>()
		)
	;
	
	// f2 możemy też użyć jako niezależnej funkcji
	boost::python::def("f22", f2);
	
	// podobnie jak f1
	boost::python::def("f11", &K1::f1);
}
