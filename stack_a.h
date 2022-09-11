#ifndef _STACK_A_H
#define _STACK_A_H
#include <iostream>

using std::size_t;

template <typename T>
class stack_a {
    T* data;
    size_t capacity, count;

    void resize_if_need();

public:
    stack_a(size_t capacity = 50'000);
    ~stack_a();

    stack_a& operator=(const stack_a& copy);
    stack_a& operator=(stack_a&& copy);

    void push(const T& elem);
    void push(T&& elem);
    void pop();
    T& top();
    T& bottom();
    const T& top() const;
    size_t size() const;
};

template <typename T>
void stack_a<T>::resize_if_need() {
    if (this->count == this->capacity) {
        size_t new_capacity = capacity * 2;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < this->capacity; ++i) {
            new_data[i] = std::move(this->data[i]);
        }
        delete[] this->data;
        this->capacity = new_capacity;
        this->data = new_data;
    }
}

template<typename T>
stack_a<T>::stack_a(size_t capacity) {
    this->data = new T[capacity];
    this->capacity = capacity;
    this->count = 0;
}


template<typename T>
stack_a<T>::~stack_a() {
    delete[] this->data;
}

//template<typename T>
//stack_a<T>& stack_a<T>::operator=(const stack_a &copy) {
//    copy.data = this->data;
//}

template<typename T>
void stack_a<T>::push(const T& elem) {
    //std::cout << "Called usual push" << std::endl;
    resize_if_need();
    this->data[count++] = elem;
}

template<typename T>
void stack_a<T>::push(T&& elem) {
    //std::cout << "Called move-push" << std::endl;
    resize_if_need();
    this->data[count++] = elem;
}

template<typename T>
void stack_a<T>::pop() {
    if (this->count > 0)
        --this->count;
}

template<typename T>
T& stack_a<T>::top() {
    return this->data[this->count - 1];
}

template<typename T>
const T& stack_a<T>::top() const {
    return this->data[this->count - 1];
}

template<typename T>
size_t stack_a<T>::size() const {
    return this->count;
}

template<typename T>
T &stack_a<T>::bottom() {
    return this->data[0];
}

#endif //_STACK_A_H
