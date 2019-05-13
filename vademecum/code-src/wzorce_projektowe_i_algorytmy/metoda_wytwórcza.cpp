
#include <iostream>

struct Product {
	virtual void info() = 0;
	virtual ~Product() {}
};

struct ProductA : public Product {
	virtual void info() {
		std::cout << "ProductA: a, b, c\n";
	}
};

struct ProductB : public Product {
	virtual void info() {
		std::cout << "ProductB: a, f, g\n";
	}
};

struct ProductFactory {
	static Product* getProduct(const std::string& type) {
		if (type == "A")
			return new ProductA();
		else if (type == "B")
			return new ProductB();
		else
			return NULL;
	}
};

int main(int argc, char *argv[]) {
	std::string id = "A";
	if (argc > 1 && argv[1][0] == 'B')
		id = "B";
	
	Product* p = ProductFactory::getProduct(id);
	p->info();
	delete p;
}
