#include <iostream>
#include <stdexcept>
#include <cstring>

// Bitset class implementation
template<class T>
class Bitset {
private:
    size_t size;
    T* data;

public:
    Bitset() : size(0), data(nullptr) {}

    Bitset(size_t size) : size(size) {
        data = new T[size]();
    }

    Bitset(size_t size, const T& val) : size(size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = val;
        }
    }

    Bitset(const Bitset<T>& other) : size(other.size) {
        data = new T[size];
        std::memcpy(data, other.data, size * sizeof(T));
    }

    Bitset<T>& operator=(const Bitset<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            std::memcpy(data, other.data, size * sizeof(T));
        }
        return *this;
    }

    void push_back(const T& value) {
        T* newData = new T[size + 1];
        std::memcpy(newData, data, size * sizeof(T));
        newData[size] = value;
        delete[] data;
        data = newData;
        ++size;
    }

    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("No elements to pop");
        }
        T* newData = new T[size - 1];
        std::memcpy(newData, data, (size - 1) * sizeof(T));
        delete[] data;
        data = newData;
        --size;
    }

    void set(size_t index, const T& value) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }

    T get(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t get_size() {
        return size;
    }

    ~Bitset() {
        delete[] data;
    }
};

// Bitmap class implementation
template<class T>
class Bitmap {
private:
    size_t width;
    size_t height;
    Bitset<T>* data;

public:
    Bitmap() : width(0), height(0), data(nullptr) {}

    Bitmap(size_t width, size_t height) : width(width), height(height) {
        data = new Bitset<T>[height];
        for (size_t i = 0; i < height; ++i) {
            data[i] = Bitset<T>(width);
        }
    }

    Bitmap(size_t width, size_t height, const T& val) : width(width), height(height) {
        data = new Bitset<T>[height];
        for (size_t i = 0; i < height; ++i) {
            data[i] = Bitset<T>(width, val);
        }
    }

    Bitmap(const Bitmap<T>& other) : width(other.width), height(other.height) {
        data = new Bitset<T>[height];
        for (size_t i = 0; i < height; ++i) {
            data[i] = other.data[i];
        }
    }

    Bitmap<T>& operator=(const Bitmap<T>& other) {
        if (this != &other) {
            delete[] data;
            width = other.width;
            height = other.height;
            data = new Bitset<T>[height];
            for (size_t i = 0; i < height; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void set(size_t x, size_t y, const T& value) {
        if (x >= width || y >= height) {
            throw std::out_of_range("Index out of range");
        }
        data[y].set(x, value);
    }

    T get(size_t x, size_t y) {
        if (x >= width || y >= height) {
            throw std::out_of_range("Index out of range");
        }
        return data[y].get(x);
    }

    size_t get_width() {
        return width;
    }

    size_t get_height() {
        return height;
    }

    ~Bitmap() {
        delete[] data;
    }
};

// BitArray class implementation
template<class T>
class BitArray {
private:
    size_t size;
    Bitset<T>* data;

public:
    BitArray() : size(0), data(nullptr) {}

    BitArray(size_t size) : size(size) {
        data = new Bitset<T>(size);
    }

    BitArray(size_t size, const T& val) : size(size) {
        data = new Bitset<T>(size, val);
    }

    BitArray(const BitArray<T>& other) : size(other.size) {
        data = new Bitset<T>(*other.data);
    }

    BitArray<T>& operator=(const BitArray<T>& other) {
        if (this != &other) {
            delete data;
            size = other.size;
            data = new Bitset<T>(*other.data);
        }
        return *this;
    }

    void push_back(const T& value) {
        data->push_back(value);
        ++size;
    }

    void pop_back() {
        data->pop_back();
        --size;
    }

    void set(size_t index, const T& value) {
        data->set(index, value);
    }

    T get(size_t index) {
        return data->get(index);
    }

    size_t get_size() {
        return size;
    }

    ~BitArray() {
        delete data;
    }
};
