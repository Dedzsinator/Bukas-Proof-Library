#pragma once
#include "../../headers/Arrays-Maps/arrays.hpp"

template<class T>
Vector<T>::Vector() {
    size = 0;
    data = nullptr;
}

template<class T>
Vector<T>::Vector(size_t size) {
    size = size;
    data = new T[size]();
    for(int i = 0; i < size; i++) {
        data[i] = 1;
    }
}

template<class T>
Vector<T>::Vector(size_t size, const T& val) {
    size = size;
    data = new T[size];
    std::fill(data, data + size, val);
}

template<class T>
Vector<T>::Vector(const Vector<T>& other) {
    size = other.size;
    data = new T[size];
    std::copy(other.data, other.data + size, data);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new T[size];
        std::copy(other.data, other.data + size, data);
    }
    return *this;
}

template<class T>
void Vector<T>::push_back(const T& value) {
    T* new_t = new T[size + 1];
    std::copy(data, data + size, new_t);
    delete[] data;
    data = new_t;
    data[size++] = value;
}

template<class T>
void Vector<T>::pop_back() {
    if (size > 0) {
        T* new_t = new T[--size];
        std::copy(data, data + size, new_t);
        delete[] data;
        data = new_t;
    }
}

template<class T>
size_t Vector<T>::getSize() const {
    return size;
}

template<class T>
void Vector<T>::resize(size_t newSize, T val) {
    T* new_t = new T[newSize];
    size_t minSize = size < newSize ? size : newSize;
    std::copy(data, data + minSize, new_t);
    if (newSize > size) {
        std::fill(new_t + size, new_t + newSize, val);
    }
    delete[] data;
    data = new_t;
    size = newSize;
}

template<class T>
Vector<T>::~Vector() {
    delete[] data;
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) {
    if (size != other.size) {
        throw "Hiba! A vektorok dimenziója nem egyezik!";
    }

    Vector<T> result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] + other.data[i];
    }

    return result;
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) {
    if (size != other.size) {
        throw "Hiba! A vektorok dimenziója nem egyezik!";
    }

    Vector<T> result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] - other.data[i];
    }

    return result;
}

template<class T>
double Vector<T>::operator*(const Vector<T>& other) {
    if (size != other.size) {
        throw "Hiba! A vektorok dimenziója nem egyezik!";
    }

    double result = 0;
    for (int i = 0; i < size; i++) {
        result += data[i] * other.data[i];
    }

    return result;
}

template<class T>
T& Vector<T>::operator[](int index) {
    if (index < 0 || index >= this->size) {
        throw "Rossz index!";
    }
    return this->data[index];
}

template<class T>
T Vector<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw "Hiba! Rossz index!";
    }

    return data[index];
}

template<class T>
void Vector<T>::print() {
    std::cout << *this;
}
