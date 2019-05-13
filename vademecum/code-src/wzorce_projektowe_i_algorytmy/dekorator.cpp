
#include <iostream>

struct Product {
	virtual ~Product() {}
	virtual void info() = 0;
};

struct ProductA : public Product {
	void info() {
		std::cout << "Product:\n";
		std::cout << "  ab\n";
	}
};

struct DecoratorX : public Product {
	DecoratorX(Product* p) {
		this->p = p;
	}
	
	void info() {
		p->info();
		std::cout << "  xx\n";
	}
protected:
	Product* p;
};

struct DecoratorY : public Product {
	DecoratorY(Product* p) {
		this->p = p;
	}
	
	void info() {
		p->info();
		std::cout << "  yy\n";
	}
protected:
	Product* p;
};

int main(int argc, char *argv[]) {
	Product* p = new ProductA();
	Product* p1 = new DecoratorX(p);
	Product* p2 = new DecoratorY(p1);
	
	p1->info();
	p2->info();
	
	delete p2;
	delete p1;
	delete p;
}
