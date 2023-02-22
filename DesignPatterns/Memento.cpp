In this example, we have an Originator class that has a state represented by a std::vector<int>. 
The Originator can create a Memento object that contains a snapshot of its current state, and it can restore its state from a Memento object. 
The Caretaker class is responsible for storing the Memento objects.

In the main function, we create an Originator object and set its initial state.
We then create a Caretaker object and save the Originator's state in a Memento object. Next, we modify the Originator's state by adding two more integers to its std::vector<int>.
We then print out the current state of the Originator, which should be 1 2 3 4 5. Finally, we restore the Originator's state from
  
#include <iostream>
#include <vector>
#include <memory>

// Memento class
class Memento {
public:
    Memento(const std::vector<int>& state) : state_(state) {}

    const std::vector<int>& GetState() const {
        return state_;
    }

private:
    std::vector<int> state_;
};

// Originator class
class Originator {
public:
    void SetState(const std::vector<int>& state) {
        state_ = state;
    }

    void AddToState(int value) {
        state_.push_back(value);
    }

    const std::vector<int>& GetState() const {
        return state_;
    }

    // Creates a memento object that contains the current state of the originator
    std::shared_ptr<Memento> CreateMemento() const {
        return std::make_shared<Memento>(state_);
    }

    // Restores the state of the originator from a memento object
    void SetMemento(const std::shared_ptr<Memento>& memento) {
        state_ = memento->GetState();
    }

private:
    std::vector<int> state_;
};

// Caretaker class
class Caretaker {
public:
    void SetMemento(const std::shared_ptr<Memento>& memento) {
        memento_ = memento;
    }

    std::shared_ptr<Memento> GetMemento() const {
        return memento_;
    }

private:
    std::shared_ptr<Memento> memento_;
};

int main() {
    // Create an originator and set its initial state
    Originator originator;
    originator.SetState({ 1, 2, 3 });

    // Create a caretaker
    Caretaker caretaker;

    // Save the originator's state
    caretaker.SetMemento(originator.CreateMemento());

    // Modify the originator's state
    originator.AddToState(4);
    originator.AddToState(5);

    // Print the current state of the originator
    std::cout << "Current state: ";
    for (int value : originator.GetState()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Restore the originator's state from the saved memento
    originator.SetMemento(caretaker.GetMemento());

    // Print the restored state of the originator
    std::cout << "Restored state: ";
    for (int value : originator.GetState()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
