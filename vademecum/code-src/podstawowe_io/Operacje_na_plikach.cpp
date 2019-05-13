
// przy kompilacji konieczne jest dodanie:
//  -lboost_filesystem -lboost_system

#include <iostream>
#include <boost/filesystem.hpp>

int main() {
	// sprawdzenie czy plik istnieje
	boost::filesystem::path pFile( "/tmp/abc.txt" );
	if (boost::filesystem::is_regular_file(pFile))
		std::cout << "istnieje\n";
	else
		std::cout << "nie istnieje\n";
	
	// listowanie katalogu i sprawdzanie typów
	boost::filesystem::path pDir( "/tmp/" );
	boost::filesystem::directory_iterator end_iter;
	boost::filesystem::directory_iterator iter(pDir);
	
	for(; iter != end_iter; ++iter) {
		if (boost::filesystem::is_regular_file(iter->path())) {
			std::cout
				<< iter->path().filename().generic_string()
				<< " jest plikiem\n";
			// wypisujemy tylko nazwę pliku
		} else if (boost::filesystem::is_directory(iter->path())) {
			std::cout
				<< iter->path().generic_string()
				<< " jest katalogiem\n";
			// wypisuje,y pełną ścieżkę
		} else {
			std::cout
				<< iter->path().generic_string()
				<< " jest czymś innym\n";
		}
	}
	
	boost::filesystem::rename("/tmp/a.txt", "/tmp/b.txt");
	boost::filesystem::remove("/tmp/b.txt");
}
