#pragma once

#include <iostream>

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
