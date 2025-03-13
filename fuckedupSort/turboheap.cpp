#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <random>
#include <immintrin.h>  // For SSE/AVX intrinsics
#include "prettynumber.cpp"

using namespace std;

// Optimized MinMaxSearch using SIMD (SSE)
template<typename T>
std::pair<T, T> optimizedMinMaxSearch(const T* data, size_t size) {
    if (size == 0) return {std::numeric_limits<T>::max(), std::numeric_limits<T>::lowest()};

    T minVal = std::numeric_limits<T>::max();
    T maxVal = std::numeric_limits<T>::lowest();

    size_t i = 0;
    if constexpr (std::is_same_v<T, int>) {
        __m128i minVec = _mm_set1_epi32(std::numeric_limits<T>::max());
        __m128i maxVec = _mm_set1_epi32(std::numeric_limits<T>::lowest());

        for (; i + 4 <= size; i += 4) {
            __m128i vec = _mm_loadu_si128(reinterpret_cast<const __m128i*>(data + i));
            minVec = _mm_min_epi32(minVec, vec);
            maxVec = _mm_max_epi32(maxVec, vec);
        }

        int minVals[4], maxVals[4];
        _mm_storeu_si128(reinterpret_cast<__m128i*>(minVals), minVec);
        _mm_storeu_si128(reinterpret_cast<__m128i*>(maxVals), maxVec);

        for (int j = 0; j < 4; ++j) {
            minVal = std::min(minVal, minVals[j]);
            maxVal = std::max(maxVal, maxVals[j]);
        }
    }

    // Handle the remaining elements
    for (; i < size; ++i) {
        minVal = std::min(minVal, data[i]);
        maxVal = std::max(maxVal, data[i]);
    }

    return {minVal, maxVal};
}

// A simple custom heap class with improved cache locality
template<typename T>
class CustomHeap {
public:
    CustomHeap(size_t initialCapacity = 16) 
        : size_(0), capacity_(initialCapacity), data_(new T[initialCapacity]) {}

    ~CustomHeap() {
        delete[] data_;
    }

    void push(const T& value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        data_[size_++] = value;
        heapifyUp(size_ - 1);
    }

    T pop() {
        if (size_ == 0) throw std::runtime_error("Heap is empty");
        T root = data_[0];
        data_[0] = data_[--size_];
        heapifyDown(0);
        return root;
    }

    size_t size() const {
        return size_;
    }

private:
    void heapifyUp(size_t index) {
        T value = data_[index];
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (value <= data_[parent]) break;
            data_[index] = data_[parent];
            index = parent;
        }
        data_[index] = value;
    }

    void heapifyDown(size_t index) {
        T value = data_[index];
        size_t half = size_ / 2;
        while (index < half) {
            size_t leftChild = 2 * index + 1;
            size_t rightChild = leftChild + 1;

            size_t largestChild = leftChild;
            if (rightChild < size_ && data_[rightChild] > data_[leftChild]) {
                largestChild = rightChild;
            }

            if (value >= data_[largestChild]) break;
            data_[index] = data_[largestChild];
            index = largestChild;
        }
        data_[index] = value;
    }

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        std::memcpy(newData, data_, size_ * sizeof(T));
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    size_t size_;
    size_t capacity_;
    T* data_;
};

// The PolarHeap class
template<typename T>
class PolarHeap {
public:
    PolarHeap(vector<T>& data) 
        : data_(data), domainTop(0), bucketSpan(16) {
        preprocess();
    }

    void heapSort() {
        buildHeap();
        for (size_t i = data_.size(); i > 1; --i) {
            std::swap(data_[0], data_[i - 1]);
            heapify(0, i - 1);
        }
    }

private:
    vector<T>& data_;
    vector<CustomHeap<T>> subHeaps_;
    T domainTop;
    int bucketSpan;

    void preprocess() {
        auto [domainBottom, domainTopGuess] = optimizedMinMaxSearch(data_.data(), data_.size());
        domainTop = domainTopGuess;

        bucketSpan = guessBucketSpan(domainBottom, domainTop);
        int slino = std::ceil(static_cast<double>(domainTop - domainBottom) / bucketSpan);
        subHeaps_ = vector<CustomHeap<T>>(slino);

        for (size_t i = 0; i < data_.size(); ++i) {
            int index = static_cast<int>(std::floor(data_[i] / bucketSpan));
            subHeaps_[index].push(data_[i]);
        }
    }

    int guessBucketSpan(T domainBottom, T domainTop) {
        if (domainTop == 0 && domainBottom == 0) return 1;

        int range = domainTop - domainBottom;
        int optimalSpan = 16; // Start with a guess (this could be fine-tuned)

        while (optimalSpan < range) {
            optimalSpan *= 2;
        }
        return optimalSpan;
    }

    void buildHeap() {
        data_ = vector<T>(data_.size());
        size_t index = 0;
        for (auto& heap : subHeaps_) {
            while (heap.size() > 0) {
                data_[index++] = heap.pop();
            }
        }
    }

    void heapify(size_t index, size_t size) {
        size_t largest = index;
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;

        if (left < size && data_[left] > data_[largest]) {
            largest = left;
        }
        if (right < size && data_[right] > data_[largest]) {
            largest = right;
        }
        if (largest != index) {
            std::swap(data_[index], data_[largest]);
            heapify(largest, size);
        }
    }
};

// The TurboHeapSort algorithm
template<typename T>
void TurboHeapSort(vector<T>& data) {
    PolarHeap<T> polarHeap(data);
    polarHeap.heapSort();
}

void printVector(const vector<int>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int N = 1000000; // Adjust N for testing
    int modulo = 10000;
    vector<int> data(N);

    // Generating random data
    std::generate(data.begin(), data.end(), [modulo]() { return rand() % modulo; });

    if (N <= 30) {
        std::cout << "Original data:\n";
        printVector(data);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Use TurboHeapSort with aggressive optimizations
    TurboHeapSort(data);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    if (N <= 30) {
        std::cout << "Sorted data:\n";
        printVector(data);
    }
  
    cout << "N = " << prettyNumber(N) << " - Modulo = " << (modulo == -1 ? "no cap " : prettyNumber(modulo)) << endl;
    cout << "Time taken: " << diff.count() << " s\n";
    cout << "Is sorted: " << (is_sorted(data.begin(), data.end()) ? "\033[1;32m[Yes]\033[0m" : "\033[1;31m[No]\033[0m") << endl;

    return 0;
}
