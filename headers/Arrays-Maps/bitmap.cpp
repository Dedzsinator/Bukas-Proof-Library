#include <iostream>

template<class T>
//bitset
class Bitset {
  private:
    size_t size;
    T* data;

  public:
    Bitset();
    Bitset(size_t size);
    Bitset(size_t size, const T& val);
    Bitset(const Bitset<T>& other);
    Bitset<T>& operator=(const Bitset<T>& other);
    void push_back(const T& value);
    void pop_back();
    void set(size_t index, const T& value);
    T get(size_t index);
    size_t get_size();
    ~Bitset();
};

template<class T>
class Bitmap {
  private:
    size_t width;
    size_t height;
    Bitset<T>* data;

  public:
    Bitmap();
    Bitmap(size_t width, size_t height);
    Bitmap(size_t width, size_t height, const T& val);
    Bitmap(const Bitmap<T>& other);
    Bitmap<T>& operator=(const Bitmap<T>& other);
    void set(size_t x, size_t y, const T& value);
    T get(size_t x, size_t y);
    size_t get_width();
    size_t get_height();
    ~Bitmap();
};

template<class T>
class BitArray {
  private:
    size_t size;
    Bitset<T>* data;

  public:
    BitArray();
    BitArray(size_t size);
    BitArray(size_t size, const T& val);
    BitArray(const BitArray<T>& other);
    BitArray<T>& operator=(const BitArray<T>& other);
    void push_back(const T& value);
    void pop_back();
    void set(size_t index, const T& value);
    T get(size_t index);
    size_t get_size();
    ~BitArray();
};
