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
constexpr int calculateNumBuckets(size_t Size) noexcept {
    return Size < 16 ? 1 : static_cast<int>(sqrt(Size));
}

// Optimized insertion sort with no inline assembly (reliable performance)
void asmInsertionSort(vector<int>& arr) noexcept {
    size_t n = arr.size();
    if (n <= 1) return;

    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        size_t j = i;

        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }

        arr[j] = key;
    }
}

// Function to distribute elements into buckets using inline assembly
void asmDistributeIntoBuckets(const vector<int>& arr, vector<vector<int>>& buckets, int numBuckets, int minVal, int range) noexcept {
    int bucketSize = (range + numBuckets - 1) / numBuckets;

    // Avoid division by zero or other invalid operations
    if (bucketSize <= 0) bucketSize = 1;

    for (size_t i = 0; i < arr.size(); ++i) {
        int value = arr[i];
        int bucketIndex;

        // Inline assembly to calculate bucket index
        __asm__ __volatile__ (
            "subl %2, %1;"           // value -= minVal
            "movl %1, %%eax;"        // eax = value
            "cltd;"                  // Sign extend eax into edx:eax for division
            "idivl %3;"              // eax = value / bucketSize, edx = remainder
            "movl %%eax, %0;"        // bucketIndex = eax
            : "=r" (bucketIndex)     // output
            : "r" (value), "r" (minVal), "r" (bucketSize) // inputs
            : "%eax", "%edx", "memory"
        );

        bucketIndex = min(max(bucketIndex, 0), numBuckets - 1);
        buckets[bucketIndex].push_back(value);
    }
}

// Bucket sort function with assembly optimizations
template<size_t Size>
void bucketSort(vector<int>& arr) noexcept {
    if (arr.empty()) return;

    constexpr int NumBuckets = calculateNumBuckets(Size);

    if (Size < 16) {
        asmInsertionSort(arr);
        return;
    }

    vector<vector<int>> buckets(NumBuckets);

    auto [minIt, maxIt] = minmax_element(arr.begin(), arr.end());
    int minVal = *minIt;
    int maxVal = *maxIt;
    int range = maxVal - minVal + 1;

    asmDistributeIntoBuckets(arr, buckets, NumBuckets, minVal, range);

    size_t index = 0;
    for (auto& bucket : buckets) {
        if (bucket.size() < 16) {
            asmInsertionSort(bucket);
        } else {
            sort(bucket.begin(), bucket.end());
        }
        copy(bucket.begin(), bucket.end(), arr.begin() + index);
        index += bucket.size();
    }
}

inline void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}


int main() {
    // Generate a number of random numbers
    const size_t N = 100000000; // Adjust N for testing
    vector<int> data(N);
    generate(data.begin(), data.end(), []() { return rand(); });

    if (N <= 30) {
        // Print original data
        cout << "Original data:\n";
        printVector(data);
    }

    // Record the time
    auto start = chrono::high_resolution_clock::now();
    bucketSort<N>(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    if (N <= 30) {
        // Print sorted data
        cout << "Sorted data:\n";
        printVector(data);
    }

    cout << "Time taken: " << diff.count() << " s\n";
    cout << "Is sorted: " << (is_sorted(data.begin(), data.end()) ? "\033[1;32m[Yes]\033[0m" : "\033[1;31m[No]\033[0m") << endl;

    return 0;
}
