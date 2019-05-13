
#include <iostream>

struct Product {
	virtual void info() = 0;
	virtual ~Product() {}
};

struct ProductA: public Product {
	virtual void info() {
		std::cout << "ProductA: a, b, c\n";
	}
};

struct ProductB: public Product {
	virtual void info() {
		std::cout << "ProductB: a, f, g\n";
	}
};

struct Factory {
	static  Factory* getFactory(const std::string& type);
	virtual Product* getProduct() = 0;
	// fabryka taka może z łatwością produkować kilka
	// różnych produktów (całą rodzinę produktów)
	virtual ~Factory() {}
};

struct FactoryA: public Factory {
	virtual Product* getProduct() {
		return new ProductA();
	}
};

struct FactoryB: public Factory {
	virtual Product* getProduct() {
		return new ProductB();
	}
};

Factory* Factory::getFactory(const std::string& type) {
	if (type == "A")
		return new FactoryA();
	else if (type == "B")
		return new FactoryB();
	else
		return NULL;
}

int main(int argc, char *argv[]) {
	std::string id = "A";
	if (argc > 1 && argv[1][0] == 'B')
		id = "B";
	
	Factory* f = Factory::getFactory(id);
	Product* p = f->getProduct();
	p->info();
	delete p;
	delete f;
}
