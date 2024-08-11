#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <cstring> // for memset, memcpy

template <typename T = uint64_t>
class BitSet {
private:
    T* bits;
    size_t numBits;
    size_t numWords;

    static constexpr size_t bitsPerWord = sizeof(T) * 8;

public:
    explicit BitSet(size_t size) : numBits(size) {
        numWords = (size + bitsPerWord - 1) / bitsPerWord;
        bits = new T[numWords];
        std::memset(bits, 0, numWords * sizeof(T));  // Initialize to 0
    }

    ~BitSet() {
        delete[] bits;
    }

    BitSet(const BitSet& other) : numBits(other.numBits), numWords(other.numWords) {
        bits = new T[numWords];
        std::memcpy(bits, other.bits, numWords * sizeof(T));
    }

    BitSet& operator=(const BitSet& other) {
        if (this != &other) {
            delete[] bits;
            numBits = other.numBits;
            numWords = other.numWords;
            bits = new T[numWords];
            std::memcpy(bits, other.bits, numWords * sizeof(T));
        }
        return *this;
    }

    void set(size_t index) {
        if (index >= numBits) throw std::out_of_range("BitSet index out of range");
        bits[index / bitsPerWord] |= (T(1) << (index % bitsPerWord));
    }

    void clear(size_t index) {
        if (index >= numBits) throw std::out_of_range("BitSet index out of range");
        bits[index / bitsPerWord] &= ~(T(1) << (index % bitsPerWord));
    }

    void toggle(size_t index) {
        if (index >= numBits) throw std::out_of_range("BitSet index out of range");
        bits[index / bitsPerWord] ^= (T(1) << (index % bitsPerWord));
    }

    bool test(size_t index) const {
        if (index >= numBits) throw std::out_of_range("BitSet index out of range");
        return (bits[index / bitsPerWord] & (T(1) << (index % bitsPerWord))) != 0;
    }

    void reset() {
        std::memset(bits, 0, numWords * sizeof(T));
    }

    size_t size() const {
        return numBits;
    }

    // Bitwise operators
    BitSet& operator|=(const BitSet& other) {
        if (numBits != other.numBits) throw std::invalid_argument("BitSet sizes do not match");
        for (size_t i = 0; i < numWords; ++i) {
            bits[i] |= other.bits[i];
        }
        return *this;
    }

    BitSet& operator&=(const BitSet& other) {
        if (numBits != other.numBits) throw std::invalid_argument("BitSet sizes do not match");
        for (size_t i = 0; i < numWords; ++i) {
            bits[i] &= other.bits[i];
        }
        return *this;
    }

    BitSet& operator^=(const BitSet& other) {
        if (numBits != other.numBits) throw std::invalid_argument("BitSet sizes do not match");
        for (size_t i = 0; i < numWords; ++i) {
            bits[i] ^= other.bits[i];
        }
        return *this;
    }

    BitSet operator~() const {
        BitSet result(*this);
        for (size_t i = 0; i < numWords; ++i) {
            result.bits[i] = ~bits[i];
        }
        return result;
    }

    friend BitSet operator|(BitSet lhs, const BitSet& rhs) {
        lhs |= rhs;
        return lhs;
    }

    friend BitSet operator&(BitSet lhs, const BitSet& rhs) {
        lhs &= rhs;
        return lhs;
    }

    friend BitSet operator^(BitSet lhs, const BitSet& rhs) {
        lhs ^= rhs;
        return lhs;
    }
};

template <typename T = uint64_t>
class Bitmap {
private:
    size_t width;
    size_t height;
    BitSet<T> bits;

    size_t getIndex(size_t x, size_t y) const {
        if (x >= width || y >= height) throw std::out_of_range("Bitmap index out of range");
        return y * width + x;
    }

public:
    Bitmap(size_t width, size_t height) : width(width), height(height), bits(width * height) {}

    void set(size_t x, size_t y) {
        bits.set(getIndex(x, y));
    }

    void clear(size_t x, size_t y) {
        bits.clear(getIndex(x, y));
    }

    void toggle(size_t x, size_t y) {
        bits.toggle(getIndex(x, y));
    }

    bool test(size_t x, size_t y) const {
        return bits.test(getIndex(x, y));
    }

    void reset() {
        bits.reset();
    }

    size_t getWidth() const {
        return width;
    }

    size_t getHeight() const {
        return height;
    }

    // Bitwise operators for Bitmap
    Bitmap& operator|=(const Bitmap& other) {
        if (width != other.width || height != other.height)
            throw std::invalid_argument("Bitmap dimensions do not match");
        bits |= other.bits;
        return *this;
    }

    Bitmap& operator&=(const Bitmap& other) {
        if (width != other.width || height != other.height)
            throw std::invalid_argument("Bitmap dimensions do not match");
        bits &= other.bits;
        return *this;
    }

    Bitmap& operator^=(const Bitmap& other) {
        if (width != other.width || height != other.height)
            throw std::invalid_argument("Bitmap dimensions do not match");
        bits ^= other.bits;
        return *this;
    }

    Bitmap operator~() const {
        Bitmap result(*this);
        result.bits = ~bits;
        return result;
    }

    friend Bitmap operator|(Bitmap lhs, const Bitmap& rhs) {
        lhs |= rhs;
        return lhs;
    }

    friend Bitmap operator&(Bitmap lhs, const Bitmap& rhs) {
        lhs &= rhs;
        return lhs;
    }

    friend Bitmap operator^(Bitmap lhs, const Bitmap& rhs) {
        lhs ^= rhs;
        return lhs;
    }
};