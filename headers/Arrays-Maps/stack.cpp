#pragma once

#include <iostream>
#include <stdexcept>

// Stack class definition
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
    Stack() : head(nullptr), count(0) {}

    ~Stack() {
        clear(*this);
    }

    void push(T value) {
        Node* newNode = new Node{value, head};
        head = newNode;
        count++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        Node* temp = head;
        T value = head->value;
        head = head->next;
        delete temp;
        count--;
        return value;
    }

    T peek() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return head->value;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    int size() {
        return count;
    }

    Stack(const Stack<T>& other) : head(nullptr), count(0) {
        copy(*this, other);
    }

    Stack<T>& operator=(const Stack<T>& other) {
        if (this != &other) {
            clear(*this);
            copy(*this, other);
        }
        return *this;
    }

    Stack(Stack<T>&& other) : head(nullptr), count(0) {
        swap(*this, other);
    }

    Stack<T>& operator=(Stack<T>&& other) {
        if (this != &other) {
            clear(*this);
            swap(*this, other);
        }
        return *this;
    }

    bool operator==(const Stack<T>& other) {
        if (count != other.count) {
            return false;
        }
        Node* current1 = head;
        Node* current2 = other.head;
        while (current1 != nullptr) {
            if (current1->value != current2->value) {
                return false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return true;
    }

    bool operator!=(const Stack<T>& other) {
        return !(*this == other);
    }

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

// Friend function implementations
template <typename U>
std::ostream& operator<<(std::ostream& os, const Stack<U>& stack) {
    typename Stack<U>::Node* current = stack.head;
    os << "Stack: ";
    while (current != nullptr) {
        os << current->value << " ";
        current = current->next;
    }
    return os;
}

template <typename U>
std::istream& operator>>(std::istream& is, Stack<U>& stack) {
    U value;
    while (is >> value) {
        stack.push(value);
    }
    return is;
}

template <typename U>
void swap(Stack<U>& first, Stack<U>& second) {
    using std::swap;
    swap(first.head, second.head);
    swap(first.count, second.count);
}

template <typename U>
void clear(Stack<U>& stack) {
    while (!stack.isEmpty()) {
        stack.pop();
    }
}

template <typename U>
void copy(Stack<U>& dest, const Stack<U>& src) {
    if (src.head == nullptr) {
        return;
    }
    typename Stack<U>::Node* current = src.head;
    typename Stack<U>::Node* prevNewNode = nullptr;
    while (current != nullptr) {
        typename Stack<U>::Node* newNode = new typename Stack<U>::Node{current->value, nullptr};
        if (prevNewNode == nullptr) {
            dest.head = newNode;
        } else {
            prevNewNode->next = newNode;
        }
        prevNewNode = newNode;
        current = current->next;
    }
    dest.count = src.count;
}

template <typename U>
void copy(Stack<U>& dest, Stack<U>&& src) {
    dest.head = src.head;
    dest.count = src.count;
    src.head = nullptr;
    src.count = 0;
}