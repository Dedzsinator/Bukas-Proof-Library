#pragma once

#include <iostream>

template <typename T>
class String {
private:
    char* data;
    int length;

public:
    String();
    String(const char* str);
    String(const String<T>& other);
    String(String<T>&& other);
    ~String();
    String<T>& operator=(const String<T>& other);
    String<T>& operator=(String<T>&& other);
    bool operator==(const String<T>& other);
    bool operator!=(const String<T>& other);
    char& operator[](int index);
    int size();
    bool isEmpty();
    void clear();
    void copy(const String<T>& other);
    void copy(String<T>&& other);
    void swap(String<T>& other);
    operator char*();
    operator const char*();
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const String<U>& str);
    template <typename U>
    friend std::istream& operator>>(std::istream& is, String<U>& str);
};
