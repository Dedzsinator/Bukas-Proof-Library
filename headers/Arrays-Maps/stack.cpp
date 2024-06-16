#pragma once

#include <iostream>

template <typename T>
class Stack {
private:
    struct Node {
        T value;
        Node* next;
    };
    Node* head;
    int count;

  public:
    Stack();

    ~Stack();

    void push(T value);

    T pop();

    T peek();

    bool isEmpty();

    int size();

    Stack(const Stack<T>& other);

    Stack<T>& operator=(const Stack<T>& other);

    Stack(Stack<T>&& other);

    Stack<T>& operator=(Stack<T>&& other);

    bool operator==(const Stack<T>& other);

    bool operator!=(const Stack<T>& other);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& stack);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Stack<U>& stack);

    template <typename U>
    friend void swap(Stack<U>& first, Stack<U>& second);

    template <typename U>
    friend void clear(Stack<U>& stack);

    template <typename U>
    friend void copy(Stack<U>& dest, const Stack<U>& src);

    template <typename U>
    friend void copy(Stack<U>& dest, Stack<U>&& src);
};
