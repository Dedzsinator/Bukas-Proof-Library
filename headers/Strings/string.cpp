#pragma once

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>

class String {
private:
    char* data;
    int length;

public:
    String();
    String(const char* str);
    String(const String& other);
    String(String&& other);
    ~String();
    String& operator=(const String& other);
    String& operator=(String&& other);
    bool operator==(const String& other);
    bool operator!=(const String& other);
    char& operator[](int index);
    int size();
    bool isEmpty();
    void clear();
    void copy(const String& other);
    void copy(String&& other);
    void swap(String& other);
    operator char*();
    operator const char*();
    String operator+(const String& other);
    String& operator+=(const String& other);
    String substr(int start, int end);
    int* find(const String& other);
    int* find(const char* str);
    int* find(char c);
    int* rfind(const String& other);
    int* rfind(const char* str);
    int* rfind(char c);
    String replace(const String& oldStr, const String& newStr);
    String replace(const char* oldStr, const char* newStr);
    String replace(char oldChar, char newChar);
    String toUpper();
    String toLower();
    String trim();
    String ltrim();
    String rtrim();
    String reverse();
    String repeat(int times);
    String strstr(const String& other);
    String strstr(const char* str);
    String strstr(char c);
    String strchr(const String& other);
    String strchr(const char* str);
    String strchr(char c);
    String strtok(const String& delimiters);
    String strtok(const char* delimiters);
    String strtok(char delimiter);
    String kmp(const String& pattern);
    String kmp(const char* pattern);
    String kmp(char pattern);
    String lps(const String& pattern);
    String lps(const char* pattern);
    String lps(char pattern);
    String rabinKarp(const String& pattern);
    String rabinKarp(const char* pattern);
    String rabinKarp(char pattern);
    String boyerMoore(const String& pattern);
    String boyerMoore(const char* pattern);
    String boyerMoore(char pattern);
    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator>>(std::istream& is, String& str);
};

// Constructor
String::String() : data(nullptr), length(0) {}

// Constructor with C-string
String::String(const char* str) {
    length = std::strlen(str);
    data = new char[length + 1];
    std::strcpy(data, str);
}

// Copy Constructor
String::String(const String& other) : data(nullptr), length(0) {
    copy(other);
}

// Move Constructor
String::String(String&& other) : data(nullptr), length(0) {
    copy(std::move(other));
}

// Destructor
String::~String() {
    delete[] data;
}

// Copy Assignment Operator
String& String::operator=(const String& other) {
    if (this != &other) {
        copy(other);
    }
    return *this;
}

// Move Assignment Operator
String& String::operator=(String&& other) {
    if (this != &other) {
        copy(std::move(other));
    }
    return *this;
}

// Equality Operator
bool String::operator==(const String& other) {
    return std::strcmp(data, other.data) == 0;
}

// Inequality Operator
bool String::operator!=(const String& other) {
    return !(*this == other);
}

// Subscript Operator
char& String::operator[](int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Size Function
int String::size() {
    return length;
}

// IsEmpty Function
bool String::isEmpty() {
    return length == 0;
}

// Clear Function
void String::clear() {
    delete[] data;
    data = nullptr;
    length = 0;
}

// Copy Function
void String::copy(const String& other) {
    delete[] data;
    length = other.length;
    data = new char[length + 1];
    std::strcpy(data, other.data);
}

// Move Copy Function
void String::copy(String&& other) {
    delete[] data;
    data = other.data;
    length = other.length;
    other.data = nullptr;
    other.length = 0;
}

// Swap Function
void String::swap(String& other) {
    std::swap(data, other.data);
    std::swap(length, other.length);
}

// Conversion to char*
String::operator char*() {
    return data;
}

// Conversion to const char*
String::operator const char*() {
    return data;
}

// Concatenation Operator
String String::operator+(const String& other) {
    String result;
    result.length = length + other.length;
    result.data = new char[result.length + 1];
    std::strcpy(result.data, data);
    std::strcat(result.data, other.data);
    return result;
}

// Concatenation Assignment Operator
String& String::operator+=(const String& other) {
    *this = *this + other;
    return *this;
}

// Substring Function
String String::substr(int start, int end) {
    if (start < 0 || end > length || start > end) {
        throw std::out_of_range("Invalid substring range");
    }
    String result;
    result.length = end - start;
    result.data = new char[result.length + 1];
    std::strncpy(result.data, data + start, result.length);
    result.data[result.length] = '\0';
    return result;
}

// Find Functions
int* String::find(const String& other) {
    return find(other.data);
}

int* String::find(const char* str) {
    char* pos = std::strstr(data, str);
    if (pos) {
        int* index = new int(pos - data);
        return index;
    }
    return nullptr;
}

int* String::find(char c) {
    char* pos = std::strchr(data, c);
    if (pos) {
        int* index = new int(pos - data);
        return index;
    }
    return nullptr;
}

// Reverse Find Functions
int* String::rfind(const String& other) {
    return rfind(other.data);
}

int* String::rfind(const char* str) {
    char* pos = std::strrchr(data, *str);
    if (pos) {
        int* index = new int(pos - data);
        return index;
    }
    return nullptr;
}

int* String::rfind(char c) {
    char* pos = std::strrchr(data, c);
    if (pos) {
        int* index = new int(pos - data);
        return index;
    }
    return nullptr;
}

// Replace Functions
String String::replace(const String& oldStr, const String& newStr) {
    return replace(oldStr.data, newStr.data);
}

String String::replace(const char* oldStr, const char* newStr) {
    String result(data);
    int* pos = result.find(oldStr);
    if (pos) {
        result = result.substr(0, *pos) + newStr + result.substr(*pos + std::strlen(oldStr), result.length);
        delete pos;
    }
    return result;
}

String String::replace(char oldChar, char newChar) {
    String result(data);
    for (int i = 0; i < result.length; ++i) {
        if (result.data[i] == oldChar) {
            result.data[i] = newChar;
        }
    }
    return result;
}

// ToUpper Function
String String::toUpper() {
    String result(data);
    for (int i = 0; i < result.length; ++i) {
        result.data[i] = std::toupper(result.data[i]);
    }
    return result;
}

// ToLower Function
String String::toLower() {
    String result(data);
    for (int i = 0; i < result.length; ++i) {
        result.data[i] = std::tolower(result.data[i]);
    }
    return result;
}

// Trim Functions
String String::trim() {
    return ltrim().rtrim();
}

String String::ltrim() {
    int start = 0;
    while (start < length && std::isspace(data[start])) {
        ++start;
    }
    return substr(start, length);
}

String String::rtrim() {
    int end = length;
    while (end > 0 && std::isspace(data[end - 1])) {
        --end;
    }
    return substr(0, end);
}

// Reverse Function
String String::reverse() {
    String result(data);
    std::reverse(result.data, result.data + result.length);
    return result;
}

// Repeat Function
String String::repeat(int times) {
    String result;
    result.length = length * times;
    result.data = new char[result.length + 1];
    for (int i = 0; i < times; ++i) {
        std::strcat(result.data, data);
    }
    return result;
}

// Stream Operators
std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.data;
    return os;
}

std::istream& operator>>(std::istream& is, String& str) {
    char buffer[1024];
    is >> buffer;
    str = String(buffer);
    return is;
}
