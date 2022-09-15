#include <iostream>
#include <memory>
using std::size_t;

#ifndef STACK_STACK_L_H
#define STACK_STACK_L_H

/* Simple list-based stack */
template <typename T>
struct cNode {
    T data;
    cNode* next;
};

template <typename T>
class cStack_l {
private:
    cNode<T>* top_elem;
    size_t count;

public:
    cStack_l();
    ~cStack_l();

    void push(const T& elem);
    void push(T&& elem);
    void pop();
    T& top();
    const T& top() const;
    constexpr size_t size();
};

template<typename T>
cStack_l<T>::cStack_l() {
    top_elem = nullptr;
    count = 0;
}

template<typename T>
cStack_l<T>::~cStack_l() {
    while (top_elem != nullptr)
        pop();

    //delete this;
}

template<typename T>
void cStack_l<T>::push(const T &elem) {
    auto* n = new cNode<T>;
    n->data = elem;
    n->next = top_elem;
    top_elem = n;
    ++count;
}

template<typename T>
void cStack_l<T>::push(T &&elem) {
    auto* n = new cNode<T>;
    n->data = elem;
    n->next = top_elem;
    top_elem = n;
    ++count;
}

template<typename T>
void cStack_l<T>::pop() {
    if (top_elem != nullptr) {
        auto* n = top_elem;
        top_elem = top_elem->next;
        delete n;
        --count;
    } else
        throw std::out_of_range("The stack is empty.");
}

template<typename T>
T &cStack_l<T>::top() {
    if (top_elem != nullptr)
        return top_elem->data;
    else
        throw std::out_of_range("The stack is empty.");
}

template<typename T>
const T &cStack_l<T>::top() const {
    if (top_elem != nullptr)
        return top_elem->data;
    else
        throw std::out_of_range("The stack is empty.");
}

template<typename T>
constexpr size_t cStack_l<T>::size() {
    return count;
}


/* С++17 list-based stack */
template <typename T>
struct node {
    T data;
    std::unique_ptr<node<T>> next;

    node(T inputData, node* inputNext) : data(inputData), next(inputNext) { }
};

template <typename T>
class stack_l {
    std::unique_ptr<node<T>> top_elem;
    size_t count{};

public:
    stack_l();
    ~stack_l();

    void push(const T& elem);
    void push(T&& elem);
    void pop();
    T& top();
    const T& top() const;
    constexpr size_t size();
};

template <typename T>
stack_l<T>::stack_l() : top_elem(nullptr), count(0) { }

template <typename T>
stack_l<T>::~stack_l() {
    while (top_elem != nullptr)
        this->pop();

    delete this;
}

template <typename T>
void stack_l<T>::push(const T& elem) {
    top_elem = std::make_unique<node<T>>(elem, top_elem.release());
    ++count;
}

template <typename T>
void stack_l<T>::push(T&& elem) {
    top_elem = std::make_unique<node<T>>(elem, top_elem.release());
    ++count;
}

template <typename T>
void stack_l<T>::pop() {
    if (top_elem != nullptr) {
        top_elem = std::move(top_elem->next);
        --count;
    } else
        throw std::out_of_range("The stack is empty.");
}

template <typename T>
T& stack_l<T>::top() {
    if (top_elem != nullptr)
        return top_elem->data;
    else
        throw std::out_of_range("The stack is empty.");
}

template<typename T>
const T& stack_l<T>::top() const {
    if (top_elem != nullptr)
        return top_elem->data;
    else
        throw std::out_of_range("The stack is empty.");
}

template <typename T>
constexpr size_t stack_l<T>::size() {
    return this->count;
}

#endif //STACK_STACK_L_H
