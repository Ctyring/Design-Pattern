// 抽象工厂模式
#include <iostream>

class Product {
   public:
    virtual void operation() = 0;
};

class ConcreteProduct1 : public Product {
   public:
    void operation() {
        std::cout << "ConcreteProduct1 operation." << std::endl;
    }
};

class ConcreteProduct2 : public Product {
   public:
    void operation() {
        std::cout << "ConcreteProduct2 operation." << std::endl;
    }
};

class AbstractFactory {
   public:
    virtual Product* createProduct() = 0;
};

class ConcreteFactory1 : public AbstractFactory {
   public:
    Product* createProduct() { return new ConcreteProduct1(); }
};

class ConcreteFactory2 : public AbstractFactory {
   public:
    Product* createProduct() { return new ConcreteProduct2(); }
};

int main() {
    AbstractFactory* factory = new ConcreteFactory1();
    Product* product = factory->createProduct();
    product->operation();
    return 0;
}
