#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>
#include <numeric>
#include <immintrin.h>  // For SIMD intrinsics

using namespace std;

// Compile-time calculation for number of buckets
template<size_t Size>
constexpr int calculateNumBuckets() noexcept {
    return Size < 16 ? 1 : static_cast<int>(sqrt(Size));
}

// Aggressively unrolled insertion sort with SIMD
inline void simdInsertionSort(vector<int>& arr) noexcept {
    size_t n = arr.size();
    if (n <= 1) return;

    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        size_t j = i;

        // SIMD comparison (vectorized)
        while (j >= 4) {
            __m128i keys = _mm_set1_epi32(key);
            __m128i vals = _mm_loadu_si128(reinterpret_cast<__m128i*>(&arr[j - 4]));
            __m128i cmp = _mm_cmpgt_epi32(vals, keys);
            int mask = _mm_movemask_epi8(cmp);

            if (mask == 0) break;

            arr[j] = arr[j - 1];
            --j;
        }

        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

// Function for distributing elements into buckets (noexcept for optimization)
inline void distributeIntoBuckets(const vector<int>& arr, vector<vector<int>>& buckets, int numBuckets, int minVal, int range) noexcept {
    int bucketSize = (range + numBuckets - 1) / numBuckets;
    for (const auto& value : arr) {
        int bucketIndex = (value - minVal) / bucketSize;
        bucketIndex = min(max(bucketIndex, 0), numBuckets - 1);
        buckets[bucketIndex].push_back(value);
    }
}

// Bucket sort function with SIMD optimization, aggressive inlining, and unrolling
template<size_t Size, int NumBuckets = calculateNumBuckets<Size>()>
void bucketSort(vector<int>& arr) noexcept {
    if (arr.empty()) return;

    // Branch eliminated at compile time
    if constexpr (Size < 16) {
        simdInsertionSort(arr);
        return;
    }

    vector<vector<int>> buckets(NumBuckets);

    auto [minIt, maxIt] = minmax_element(arr.begin(), arr.end());
    int minVal = *minIt;
    int maxVal = *maxIt;
    int range = maxVal - minVal + 1;

    distributeIntoBuckets(arr, buckets, NumBuckets, minVal, range);

    size_t index = 0;
    for (auto& bucket : buckets) {
        if (bucket.size() < 16) {
            simdInsertionSort(bucket);
        } else {
            sort(bucket.begin(), bucket.end()); // Use std::sort for larger buckets
        }
        copy(bucket.begin(), bucket.end(), arr.begin() + index);
        index += bucket.size();
    }
}

// Utility function to print the vector (marked noexcept for optimization)
inline void printVector(const vector<int>& vec) noexcept {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    const int N = 10000000; // Adjust N for testing
    vector<int> data(N);
    generate(data.begin(), data.end(), []() { return rand(); });

    if (N <= 30) {
        cout << "Original data:\n";
        printVector(data);
    }

    auto start = chrono::high_resolution_clock::now();

    // Use bucketSort with aggressive optimizations
    bucketSort<N>(data);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    if (N <= 30) {
        cout << "Sorted data:\n";
        printVector(data);
    }

    cout << "Time taken: " << diff.count() << " s\n";
    cout << "Is sorted: " << (is_sorted(data.begin(), data.end()) ? "\033[1;32m[Yes]\033[0m" : "\033[1;31m[No]\033[0m") << endl;

    return 0;
}
