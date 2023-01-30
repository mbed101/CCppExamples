#include <iostream>
#include <vector>

class Observer {
 public:
  virtual void update() = 0;
};

class Subject {
 private:
  std::vector<Observer*> observers_;

 public:
  void attach(Observer *observer) {
    observers_.push_back(observer);
  }

  void detach(Observer *observer) {
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end());
  }

  void notify() {
    for (Observer *observer : observers_) {
      observer->update();
    }
  }
};

class ConcreteObserverA : public Observer {
 public:
  void update() {
    std::cout << "ConcreteObserverA received update." << std::endl;
  }
};

class ConcreteObserverB : public Observer {
 public:
  void update() {
    std::cout << "ConcreteObserverB received update." << std::endl;
  }
};

int main() {
  Subject subject;
  ConcreteObserverA observerA;
  ConcreteObserverB observerB;

  subject.attach(&observerA);
  subject.attach(&observerB);

  subject.notify();
  return 0;
}
