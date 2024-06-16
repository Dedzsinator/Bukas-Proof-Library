#pragma once

#include <iostream>

template <typename T>
class Set {
private:
    struct Node {
        T value;
        Node* next;
    };
    Node* head;
    int count;

  public:
    Set();

    ~Set();

    void add(T value);

    void remove(T value);

    bool contains(T value);

    bool isEmpty();

    int size();

    Set(const Set<T>& other);

    Set<T>& operator=(const Set<T>& other);

    Set(Set<T>&& other);

    Set<T>& operator=(Set<T>&& other);

    bool operator==(const Set<T>& other);

    bool operator!=(const Set<T>& other);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Set<U>& set);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Set<U>& set);

    template <typename U>
    friend void swap(Set<U>& first, Set<U>& second);

    template <typename U>
    friend void clear(Set<U>& set);

    template <typename U>
    friend void copy(Set<U>& dest, const Set<U>& src);

    template <typename U>
    friend void copy(Set<U>& dest, Set<U>&& src);
};
