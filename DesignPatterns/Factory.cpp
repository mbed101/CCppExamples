#include <iostream>
#include <map>
#include <memory>
#include <string>

class Product {
 public:
  virtual void operation() = 0;
  virtual ~Product() {}
};

class ConcreteProductA : public Product {
 public:
  void operation() {
    std::cout << "I am ConcreteProductA." << std::endl;
  }
};

class ConcreteProductB : public Product {
 public:
  void operation() {
    std::cout << "I am ConcreteProductB." << std::endl;
  }
};

class Factory {
 public:
  static std::unique_ptr<Product> createProduct(std::string productName) {
    if (productName == "A") {
      return std::make_unique<ConcreteProductA>();
    } else if (productName == "B") {
      return std::make_unique<ConcreteProductB>();
    }
    return nullptr;
  }
};

int main() {
  auto productA = Factory::createProduct("A");
  productA->operation();

  auto productB = Factory::createProduct("B");
  productB->operation();
  return 0;
}
