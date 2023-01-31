#include <iostream>

class Example {
  public:
    Example() : x_(0) {}

    void Increment() {
        ++x_;
    }

    int GetX() const {
        return x_;
    }

  private:
    int x_;
};

int main() {
    const Example example;

    // The following line generates a compiler error without the 'mutable' keyword:
    // error: assignment of member 'Example::x_' in read-only object
    // example.x_ = 42;

    // The following line compiles without error with the 'mutable' keyword:
    example.Increment();

    std::cout << example.GetX() << std::endl;

    return 0;
}
