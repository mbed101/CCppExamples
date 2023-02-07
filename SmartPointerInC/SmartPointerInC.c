#include <stdlib.h>
#include <pthread.h>

typedef struct smart_pointer {
    int *ptr;
    int count;
    pthread_mutex_t lock;
} smart_pointer;

smart_pointer *make_smart_pointer(int *ptr) {
    smart_pointer *sp = (smart_pointer *) malloc(sizeof(smart_pointer));
    sp->ptr = ptr;
    sp->count = 1;
    pthread_mutex_init(&sp->lock, NULL);
    return sp;
}

void increment_count(smart_pointer *sp) {
    pthread_mutex_lock(&sp->lock);
    sp->count++;
    pthread_mutex_unlock(&sp->lock);
}

void decrement_count(smart_pointer *sp) {
    pthread_mutex_lock(&sp->lock);
    sp->count--;
    if (sp->count == 0) {
        pthread_mutex_unlock(&sp->lock);
        pthread_mutex_destroy(&sp->lock);
        free(sp->ptr);
        free(sp);
    } else {
        pthread_mutex_unlock(&sp->lock);
    }
}

int main() {
    int *ptr = (int *) malloc(sizeof(int));
    *ptr = 5;
    smart_pointer *sp = make_smart_pointer(ptr);
    increment_count(sp);
    decrement_count(sp);
    return 0;
}

In this example, the smart_pointer struct contains three fields: ptr, which is a pointer to the dynamically allocated memory, count, which is an integer that keeps track of the number of references to the memory, and lock, which is a mutex that is used to synchronize access to the smart pointer in a multithreaded environment.

The make_smart_pointer function creates a new smart pointer, initializes the reference count to 1, and initializes the mutex using pthread_mutex_init. The increment_count and decrement_count functions use a mutex to synchronize access to the smart pointer, incrementing and decrementing the reference count as needed. When the reference count reaches zero, the mutex is destroyed using pthread_mutex_destroy, and the memory is freed using the free function.

This example demonstrates how a smart pointer can be used to simplify memory management and provide thread-safety, while still providing low-level control over the memory allocation and deallocation process. By using a smart pointer, you can improve the overall quality and reliability of your code, and reduce the risk of memory leaks and other performance problems.
