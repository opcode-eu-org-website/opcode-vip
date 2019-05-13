
#include <iostream>
#include <map>

struct Receiver {
	virtual void receive(std::string msg) = 0;
};

struct Mediator {
	void addReceiver(Receiver* l, int key) {
		// sprawdź czy jest już zarejestrowany
		auto subset = receivers.equal_range(key);
		for (auto iter=subset.first; iter!=subset.second; ++iter)
			if (iter->second == l) return;

		// zarejestruj
		receivers.insert(std::pair<int, Receiver*>(key, l));
	}
	
	void remReceiver(Receiver* l) {
		for (auto iter=receivers.begin(); iter!=receivers.end(); ++iter) {
			if (iter->second == l) {
				receivers.erase(iter);
				return;
			}
		}
	}
	
	bool send(std::string msg, int dstID) {
		// gdyby zamiast natychmiastowego wywoływania receive() u adresatów
		// zaimplementować gromadzenie wiadomości w jakiejś strukturze
		// i osobną funkcję wysyłającą kolejne wiadomości z tej struktury
		// to wzorzec ten pozwoliłby na realizację kolejki wiadomości 
		// (pętli komunikatów)
		// 
		// struktura przechowująca zakolejkowane do wysłania wiadomości może
		// uwzględniać kolejność ich odebrania przez Mediatora lub wartość
		// priorytetu zawartego w wiadomości (kolejka priorytetowa)
		auto subset = receivers.equal_range(dstID);
		for (auto& iter=subset.first; iter!=subset.second; ++iter) {
			iter->second->receive(msg);
		}
	}

protected:
	std::multimap<int, Receiver*> receivers;
};
