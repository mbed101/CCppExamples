#include <iostream>
#include <array>
#include <mutex>

template <typename T, size_t Size>
class CircularBuffer {
  public:
    CircularBuffer() : head_(0), tail_(0) {}

    void Push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        buffer_[head_] = item;
        head_ = (head_ + 1) % Size;

        if (head_ == tail_) {
            tail_ = (tail_ + 1) % Size;
        }
    }

    T Pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (empty()) {
            throw std::runtime_error("Circular buffer is empty");
        }

        T item = buffer_[tail_];
        tail_ = (tail_ + 1) % Size;
        return item;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return head_ == tail_;
    }

    bool full() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return (head_ + 1) % Size == tail_;
    }

  private:
    std::array<T, Size> buffer_;
    size_t head_;
    size_t tail_;
    mutable std::mutex mutex_;
};

int main() {
    CircularBuffer<int, 5> cb;

    for (int i = 0; i < 5; i++) {
        cb.Push(i);
    }

    while (!cb.empty()) {
        std::cout << cb.Pop() << std::endl;
    }

    return 0;
}
