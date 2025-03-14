#include <iostream>
#include "prettynumber.cpp"
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
#include <immintrin.h>  // For SIMD operations (if available)
#include <chrono>

using namespace std;
// Custom aligned allocator
template <typename T>
struct AlignedAllocator {
    using value_type = T;
    AlignedAllocator() noexcept {}

    template <typename U>
    AlignedAllocator(const AlignedAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        void* ptr = _mm_malloc(n * sizeof(T), 64); // 64-byte alignment
        if (!ptr) throw std::bad_alloc();
        return static_cast<T*>(ptr);
    }

    void deallocate(T* p, std::size_t) noexcept {
        _mm_free(p);
    }
};

template <typename T, typename Allocator = AlignedAllocator<T>>
using AlignedVector = std::vector<T, Allocator>;

// Radix sort helper functions
constexpr int BITS_PER_BYTE = 8;
constexpr int RADIX = 256;  // Base for radix sort (8-bit numbers)

void countingSort(AlignedVector<uint32_t>& array, int exp) {
    const size_t size = array.size();
    AlignedVector<uint32_t> output(size);
    std::vector<uint32_t> count(RADIX, 0);

    // Counting occurrences
    for (size_t i = 0; i < size; ++i) {
        ++count[(array[i] >> exp) & 0xFF];
    }

    // Cumulative count
    for (int i = 1; i < RADIX; ++i) {
        count[i] += count[i - 1];
    }

    // Place elements in sorted order
    for (size_t i = size; i > 0; --i) {
        output[count[(array[i - 1] >> exp) & 0xFF] - 1] = array[i - 1];
        --count[(array[i - 1] >> exp) & 0xFF];
    }

    // Copy the output array back to the original array
    std::copy(output.begin(), output.end(), array.begin());
}

void radixSort(AlignedVector<uint32_t>& array) {
    if (array.empty()) return;

    // Determine the maximum number to figure out the number of digits
    uint32_t maxVal = *std::max_element(array.begin(), array.end());

    // Perform counting sort for each digit
    for (int exp = 0; maxVal >> exp > 0; exp += BITS_PER_BYTE) {
        countingSort(array, exp);
    }
}

// Main function to test the sorting
int main() {
    constexpr size_t N = 1000000; // 100 million elements
    int modulo = 100000;
    AlignedVector<uint32_t> data(N);

    // Initialize array with random values
    std::generate(data.begin(), data.end(), [modulo]() { return rand() % modulo; });

    // Sort the array
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    radixSort(data);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    // Calculate the time taken
    chrono::duration<double> diff = chrono::duration_cast<chrono::duration<double>>(end - begin);

    cout << "N = " << prettyNumber(N) << " - Modulo = " << (modulo == -1 ? "no cap " : prettyNumber(modulo)) << endl;
    cout << "Time taken: " << diff.count() << " s\n";
    cout << "Is sorted: " << (is_sorted(data.begin(), data.end()) ? "\033[1;32m[Yes]\033[0m" : "\033[1;31m[No]\033[0m") << endl;
    return 0;
}
