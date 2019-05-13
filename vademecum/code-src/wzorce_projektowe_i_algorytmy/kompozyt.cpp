
#include <iostream>
#include <list>

struct Product {
	virtual void info() = 0;
	virtual ~Product() {};
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

class ProductComposite : public Product {
public:
	std::list<Product*> elements;
	
	virtual void info() {
		for (auto e : elements)
			e->info();
	}
	
	~ProductComposite() {
		for (auto e : elements)
			delete e;
	}
};

int main(int argc, char *argv[]) {
	ProductComposite* pc = new ProductComposite();
	
	pc->elements.push_back(new ProductA());
	pc->elements.push_back(new ProductB());
	pc->elements.push_back(new ProductA());
	
	pc->info();
	delete pc;
}
