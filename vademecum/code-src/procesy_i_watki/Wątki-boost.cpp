
// przy kompilacji konieczne jest dodanie:
//  -lboost_system -lboost_thread -lpthread
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include <queue>
#include <string>
#include <iostream>

std::queue<std::string> kolejka;

class Watek1 {
	Watek1(const Watek1&);
public:
	int abc;
	boost::mutex mutex;
	// boost oferuje także mutx'a pozwalającego na tworzenie kolejnych
	// blokad przez wątek który utworzył pierwszą - boost::recursive_mutex
	
	Watek1() {}
	
	void operator()() {
		for (int i=0; i<8; i++) {
			if (mutex.try_lock()) {
				abc += 1;
				std::cout << "wątek, abc= " << abc << std::endl;
				mutex.unlock();
			} else {
				std::cout << "wątek nie dostałem mutex'a ..." << std::endl;
			}
			boost::this_thread::sleep(boost::posix_time::millisec(500));
		}
		
		for (int i=0; i<8; i++) {
			boost::this_thread::sleep(boost::posix_time::millisec(700));
			boost::mutex::scoped_lock scoped_lock(mutex);
			// powyższy lock (na mutexie tego wątku)
			// blokuje od teraz do końca bloku
			
			if (!kolejka.empty()) {
				std::cout << i << ") odebrałem z kolejki \
					" << kolejka.front() << std::endl;
				kolejka.pop();
			} else {
				std::cout << i << ") kolejka pusta" << std::endl;
			}
		}
		
	}
};

int main() {
	// przygotowanie danych wątku
	Watek1 wf1;
	wf1.abc=56;
	
	// uruchomienie wątku ...
	// boost::ref() potrzebne bo obiekty klasy Watek1 są niekopiowalne
	boost::thread watek1(boost::ref(wf1));
	
	boost::this_thread::sleep(boost::posix_time::millisec(1500));
	
	// manipulacja danymi wątku
	wf1.mutex.lock();
	wf1.abc=13;
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	wf1.mutex.unlock();
	
	// obsługa kolejki
	wf1.mutex.lock();
	kolejka.push("Ala ma kota");
	kolejka.push("Kot ma Ale");
	wf1.mutex.unlock();
	
	std::cout << "2 pierwsze elementy są w kolejce" << std::endl;
	boost::this_thread::sleep(boost::posix_time::seconds(4));
	
	wf1.mutex.lock();
	kolejka.push("Abecadlo");
	kolejka.push("z pieca spadlo");
	wf1.mutex.unlock();
	
	std::cout << "2 kolejne elementy sa w kolejce" << std::endl;
	
	// czekamy na zakończenie wątku
	watek1.join();
}
