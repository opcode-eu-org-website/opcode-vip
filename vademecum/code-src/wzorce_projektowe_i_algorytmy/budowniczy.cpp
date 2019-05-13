
#include <iostream>

struct Product {
	void info() {
		std::cout << "Product:\n";
		std::cout << "  " << el1 << "\n";
		std::cout << "  " << el2 << "\n";
	}
	void setElement1(const std::string& e) {
		el1 = e;
	}
	void setElement2(const std::string& e) {
		el2 = e;
	}
private:
	std::string el1, el2;
};

struct ProductBuilder {
	virtual ~ProductBuilder() {}
	
	void createProduct() {
		p = new Product();
	}
	Product* getProduct() {
		return p;
	}
	// w takiej implementacji nie odebranie lub
	// nie skasowanie produktu przez klienta będzie
	// prowadziło do wycieków pamięci
	
	virtual void buildElement1(const std::string& d) = 0;
	virtual void buildElement2() = 0;
	
protected:
	Product* p;
};

struct ProductDirector {
	void setData(const std::string& d) {
		this->d = d;
	}
	void setBuilder(ProductBuilder* b) {
		this->b = b;
	}
	void createProduct() {
		b->createProduct();
		b->buildElement1(d);
		b->buildElement2();
	}
private:
	ProductBuilder* b;
	std::string d;
};

struct ProductBuilderA : public ProductBuilder {
	void buildElement1(const std::string& d) {
		p->setElement1(d + d);
	};
	void buildElement2() {
		p->setElement2("ab");
	};
};

struct ProductBuilderB : public ProductBuilder {
	void buildElement1(const std::string& d) {
		p->setElement1("b" + d);
	};
	void buildElement2() {
		p->setElement2("bb");
	};
};

int main(int argc, char *argv[]) {
	ProductBuilder* b;
	if (argc > 1 && argv[1][0] == 'B')
		b = new ProductBuilderB();
	else
		b = new ProductBuilderA();
	
	ProductDirector* d = new ProductDirector();
	d->setData("x");
	d->setBuilder(b);
	d->createProduct();
	
	Product* p = b->getProduct();
	p->info();
	delete p;
	delete d;
	delete b;
}
