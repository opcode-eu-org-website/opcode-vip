
/*  PLIK: py_run.cpp      kompilacja:
		g++ -I/usr/include/python3.7m/ py_run.cpp -lpython3.7m -lboost_python37
	uwaga: - kolejność argumentów może być istotna
	       - plik używa "py_api.cpp" z poprzedniego przykładu
	       - plik wywołuje skrypt "py_run.script.py" z bieżącego katalogu
*/

// korzystamy z wcześniej przygotowanego (w "API pythonowe biblioteki C++") interfejsu pythonowego
#include "py_api.cpp"

int main(int, char **) {
	K1 *o1 = new K1();
	o1->a = 1;

	K1 *o2 = new K1();
	o2->a = 2;
	
	K1::obj = o1;

	std::cout << "o1->a = " << o1->a << "   o2->a = " << o2->a << "\n";
	
	// initialise python
	Py_Initialize();
	
	try {
		// initialise and import MyPyAPI module
		PyObject* module = PyInit_MyPyAPI();
		PyDict_SetItemString(PyImport_GetModuleDict(), "MyPyAPI", module);
		Py_DECREF(module);
		PyRun_SimpleString("import MyPyAPI" );
		// poprzez PyRun_SimpleString można też uruchamiać inne fragmenty kodu pythonowego
		
		// prepare to run scripts
		boost::python::object main = boost::python::import("__main__");
		boost::python::object global(main.attr("__dict__"));
		
		// export object to python
		global["ck1"] = boost::python::ptr(o1);
		
		// run file
		boost::python::object result = boost::python::exec_file(
			"./py_run.script.py", global, global
		);
		
		// import object from python
		boost::python::object script = global["script1"];
		
		// run python function with args from C++
		if(!script.is_none()) {
				// run scripts
				std::cout << "RUN\n";
				std::cout << "return = " << boost::python::extract<int>(
					script(boost::python::ptr(o2))
				) << "\n";
		}
	} catch(boost::python::error_already_set &) {
		PyErr_Print();
		exit(-1);
	}
	
	std::cout << "o1->a = " << o1->a << "   o2->a = " << o2->a << "\n";
	
	delete o1;
	delete o2;
	
	return 0;
}
