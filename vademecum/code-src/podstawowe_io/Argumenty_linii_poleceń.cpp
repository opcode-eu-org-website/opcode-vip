
// przy kompilacji konieczne jest dodanie:
//  -lboost_program_options

#include <boost/program_options.hpp>
#include <iostream>

// pełna deklaracja funkcji main dla systemów POSIX
// funkcja main otrzymuje:
// - liczbę elementów tablicy argumentów
// - tablicę argumentów (jest to tablica napisów typu C)
// - tablicę zmiennych środowiskowych
int main(int argc, char *argv[], char *envp[]) {
	std::cout << "program wywołano z " << argc << " argumentami\n";
	for (int i=0; i<argc; ++i)
		std::cout << "argument " << i << " to: " << argv[i] << "\n";
	
	// deklaracja opcji linii poleceń
	boost::program_options::options_description desc("Program options");
	desc.add_options()
		("help,h", "show help message")
		("load", boost::program_options::value<std::string>(),
			"load from \"arg\" file")
	;
	
	// parsowanie opcji linii poleceń wraz z obsługą wyjątków
	boost::program_options::variables_map vm;
	try {
		boost::program_options::store(
			boost::program_options::parse_command_line(argc, argv, desc), vm
		);
		boost::program_options::notify(vm);
	} catch(boost::program_options::error& e) {
		std::cerr << "Cmdline args error: " << e.what() << "\n\n";
		std::cerr << "Use --help to see full options description\n";
		return 2;
	}
	
	// przetwarzanie otrzymanych opcji
	if (vm.count("help")) {
		std::cout << desc << "\n";
	} else if (vm.count("load")) {
		std::cout << "Load from: " << vm["load"].as<std::string>() << "\n";
	} else {
		std::cout << "Wywołano bez opcji\n";
	}
	
	// jest też funkcja getopt_long() z biblioteki standardowej C
	
	// funkcja main powinna zwracać kod powrotu
	// typowo: gdy program zakończy się powodzeniem zero
	//         a gdy zakończy się błędem (nie zerowy) kod błędu
	return 0;
}
