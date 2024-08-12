#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class Set {
private:
    struct Node {
        T value;
        Node* next;
    };
    Node* head;
    int count;

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        count = 0;
    }

    void copy(const Set<T>& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                add(current->value);
                current = current->next;
            }
        }
    }

    void copy(Set<T>&& other) {
        if (this != &other) {
            clear();
            head = other.head;
            count = other.count;
            other.head = nullptr;
            other.count = 0;
        }
    }

public:
    Set() : head(nullptr), count(0) {}

    ~Set() {
        clear();
    }

    void add(T value) {
        if (!contains(value)) {
            Node* newNode = new Node{value, head};
            head = newNode;
            ++count;
        }
    }

    bool remove(T value) {
        if (isEmpty()) {
            throw std::out_of_range("Set is empty");
        }

        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->value == value) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                --count;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    bool contains(T value) const{
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool isEmpty() {
        return count == 0;
    }

    int size() {
        return count;
    }

    Set(const Set<T>& other) : head(nullptr), count(0) {
        copy(other);
    }

    Set<T>& operator=(const Set<T>& other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    Set(Set<T>&& other) : head(nullptr), count(0) {
        copy(std::move(other));
    }

    Set<T>& operator=(Set<T>&& other) {
        if (this != &other) {
            copy(std::move(other));
        }
        return *this;
    }

    bool operator==(const Set<T>& other) {
        if (count != other.count) {
            return false;
        }
        Node* current = head;
        while (current != nullptr) {
            if (!other.contains(current->value)) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    bool operator!=(const Set<T>& other) {
        return !(*this == other);
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Set<U>& set) {
        typename Set<U>::Node* current = set.head;
        os << "{ ";
        while (current != nullptr) {
            os << current->value << " ";
            current = current->next;
        }
        os << "}";
        return os;
    }
    
    T& operator[](T value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return current->value;
            }
            current = current->next;
        }
        throw std::out_of_range("Value not found in set");
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Set<U>& set) {
        U value;
        while (is >> value) {
            set.add(value);
        }
        return is;
    }

    template <typename U>
    friend void swap(Set<U>& first, Set<U>& second) {
        std::swap(first.head, second.head);
        std::swap(first.count, second.count);
    }

    template <typename U>
    friend void clear(Set<U>& set) {
        set.clear();
    }

    template <typename U>
    friend void copy(Set<U>& dest, const Set<U>& src) {
        dest.copy(src);
    }

    template <typename U>
    friend void copy(Set<U>& dest, Set<U>&& src) {
        dest.copy(std::move(src));
    }
};
