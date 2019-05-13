
#include <iostream>
#include <map>

struct Obserwator {
	virtual bool onUpdate(int eventID) = 0;
};

struct Obserwowany {
	void addListener(Obserwator* l, int key) {
		// sprawdź czy jest już zarejestrowany
		auto subset = listeners.equal_range(key);
		for (auto iter=subset.first; iter!=subset.second; ++iter)
			if (iter->second == l) return;

		// zarejestruj
		listeners.insert(std::pair<int, Obserwator*>(key, l));
	}
	
	void remListener(Obserwator* l) {
		for (auto iter=listeners.begin(); iter!=listeners.end(); ++iter) {
			if (iter->second == l) {
				listeners.erase(iter);
				return;
			}
		}
	}
	
	// klasyczny wzorzec listenera
	void callListenersAll(int eventID) {
		// mapa zapewnia wywoływanie listenerów wg kolejności kluczy
		for (auto& l : listeners) {
			l.second->onUpdate(eventID);
		}
	}
	
	// wzorzec listenera połączony z łańcuchem zobowiązań
	void callListeners(int eventID) {
		// mapa zapewnia wywoływanie listenerów wg kolejności kluczy
		for (auto& l : listeners) {
			if (l.second->onUpdate(eventID))
				break;
		}
	}
	
protected:
	std::multimap<int, Obserwator*> listeners;
};

struct ObserwatorA : public Obserwator {
	virtual bool onUpdate(int eventID) {
		std::cout << " ObserwatorA z id=" << eventID << "\n";
		if (eventID == 4)
			return true;
		return false;
	};
};

struct ObserwatorB : public Obserwator {
	virtual bool onUpdate(int eventID) {
		std::cout << " ObserwatorB z id=" << eventID << "\n";
		if (eventID == 7)
			return true;
		return false;
	};
};

int main(int argc, char *argv[]) {
	Obserwowany* o = new Obserwowany();
	Obserwator* o1 = new ObserwatorA();
	Obserwator* o2 = new ObserwatorA();
	Obserwator* o3 = new ObserwatorB();
	
	o->addListener(o1, 30);
	o->addListener(o2, 10);
	o->addListener(o3, 20);
	
	std::cout << "callAll:\n";
	o->callListenersAll(7);
	
	std::cout << "call:\n";
	o->callListeners(7);
	
	delete o;
	delete o1;
	delete o2;
	delete o3;
}
