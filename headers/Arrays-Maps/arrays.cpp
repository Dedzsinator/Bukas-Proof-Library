#pragma once
#include <iostream>
using namespace std;

template<class T>
class Vector {
private:
    size_t size;
    T* data;

public:
    Vector() {
        size = 0;
        data = nullptr;
    }

    Vector(size_t size) {
        size = size;
        data = new T[size]();
        for(int i = 0; i < size; i++) {
            data[i] = 1;
        }
    }

    Vector(size_t size, const T& val) {
        size = size;
        data = new T[size];
        std::fill(data, data + size, val);
    }

    Vector(const Vector<T>& other) {
        size = other.size;
        data = new T[size];
        std::copy(other.data, other.data + size, data);
    }


    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }


    void push_back(const T& value) {
        T* new_t = new T[size + 1];
        std::copy(data, data + size, new_t);
        delete[] data;
        data = new_t;
        data[size++] = value;
    }


    void pop_back() {
        if (size > 0) {
            T* new_t = new T[--size];
            std::copy(data, data + size, new_t);
            delete[] data;
            data = new_t;
        }
    }


    size_t getSize() const {
        return size;
    }


    void resize(size_t newSize, T val) {
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

    ~Vector() {
        delete[] data;
    }


    Vector<T> operator+(const Vector<T>& other) {
        if (size != other.size) {
            throw "Hiba! A vektorok dimenziója nem egyezik!";
        }

        Vector<T> result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }


    Vector<T> operator-(const Vector<T>& other) {
        if (size != other.size) {
            throw "Hiba! A vektorok dimenziója nem egyezik!";
        }

        Vector<T> result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] - other.data[i];
        }

        return result;
    }


    double operator*(const Vector<T>& other) {
        if (size != other.size) {
            throw "Hiba! A vektorok dimenziója nem egyezik!";
        }

        double result = 0;
        for (int i = 0; i < size; i++) {
            result += data[i] * other.data[i];
        }

        return result;
    }


    T& operator[](int index) {
        if (index < 0 || index >= this->size) {
            throw "Rossz index!";
        }
        return this->data[index];
    }


    T operator[](int index) const {
        if (index < 0 || index >= size) {
            throw "Hiba! Rossz index!";
        }

        return data[index];
    }


    void print() {
        std::cout << *this;
    }

};

template<class T>
class SparseVector {
    struct pair {
        size_t index;
        T value;
    };

private:
    size_t size;
    pair* data;

public:
    SparseVector() {
        size = 0;
        data = nullptr;
    }

    SparseVector(size_t size) {
        size = size;
        data = new pair[size];
    }

    SparseVector(size_t size, const T& val) {
        size = size;
        data = new pair[size];
        for (int i = 0; i < size; i++) {
            data[i].index = i;
            data[i].value = val;
        }
    }

    SparseVector(const SparseVector<T>& other) {
        size = other.size;
        data = new pair[size];
        std::copy(other.data, other.data + size, data);
    }

    SparseVector<T>& operator=(const SparseVector<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new pair[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    void push_back(const T& value) {
        pair* new_t = new pair[size + 1];
        std::copy(data, data + size, new_t);
        delete[] data;
        data = new_t;
        data[size].index = size;
        data[size++].value = value;
    }

    void pop_back() {
        if (size > 0) {
            pair* new_t = new pair[--size];
            std::copy(data, data + size, new_t);
            delete[] data;
            data = new_t;
        }
    }

    size_t getSize() const {
        return size;
    }

    void resize(size_t newSize, T val) {
        pair* new_t = new pair[newSize];
        size_t minSize = size < newSize ? size : newSize;
        std::copy(data, data + minSize, new_t);
        if (newSize > size) {
            for (int i = size; i < newSize; i++) {
                new_t[i].index = i;
                new_t[i].value = val;
            }
        }
        delete[] data;
        data = new_t;
        size = newSize;
    }

    ~SparseVector() {
        delete[] data;
    }

    SparseVector<T> operator+(const SparseVector<T>& other) {
        if (size != other.size) {
            throw "Hiba! A vektorok dimenziója nem egyezik!";
        }

        SparseVector<T> result(size);
        for (int i = 0; i < size; i++) {
            result.data[i].index = data[i].index;
            result.data[i].value = data[i].value + other.data[i].value;
        }

        return result;
    }

    SparseVector<T> operator-(const SparseVector<T>& other) {
        if (size != other.size) {
            throw "Hiba! A vektorok dimenziója nem egyezik!";
        }

        SparseVector<T> result(size);
        for (int i = 0; i < size; i++) {
            result.data[i].index = data[i].index;
            result.data[i].value = data[i].value - other.data[i].value;
        }

        return result;
    }

    double operator*(const SparseVector<T>& other) {
        if (size != other.size) {
            throw "Hiba! A vektorok dimenziója nem egyezik!";
        }

        double result = 0;
        for (int i = 0; i < size; i++) {
            result += data[i].value * other.data[i].value;
        }

        return result;
    }

    T& operator[](int index) {
        if (index < 0 || index >= this->size) {
            throw "Rossz index!";
        }
        return this->data[index].value;
    }

    T operator[](int index) const {
        if (index < 0 || index >= size) {
            throw "Hiba! Rossz index!";
        }

        return data[index].value;
    }

    void print() {
        std::cout << *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const SparseVector<T>& v) {
        for (int i = 0; i < v.size; i++) {
            os << v.data[i].index << ": " << v.data[i].value << std::endl;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, SparseVector<T>& v) {
        for (int i = 0; i < v.size; i++) {
            is >> v.data[i].index >> v.data[i].value;
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
        for (int i = 0; i < v.size; i++) {
            os << v.data[i] << " ";
        }
        os << std::endl;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector<T>& v) {
        for (int i = 0; i < v.size; i++) {
            is >> v.data[i];
        }
        return is;
    }
};