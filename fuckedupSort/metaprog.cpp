#include "prettynumber.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>
#include <numeric>

using namespace std;

// Compile-time calculation for number of buckets
template<size_t Size>
constexpr int calculateNumBuckets() noexcept {
    return Size < 16 ? 1 : static_cast<int>(sqrt(Size));
}

// Unrolled insertion sort template (unroll up to N = 4)
template<int N>
void unrolledInsertionSort(vector<int>& arr, size_t size) noexcept {
    if (size <= N) {
        for (size_t i = 1; i < size; ++i) {
            int key = arr[i];
            size_t j = i;
            while (j > 0 && arr[j - 1] > key) {
                arr[j] = arr[j - 1];
                --j;
            }
            arr[j] = key;
        }
    } else {
        unrolledInsertionSort<N - 1>(arr, size);
    }
}

// Base case for unrolled insertion sort (N = 1)
template<>
void unrolledInsertionSort<1>(vector<int>& arr, size_t size) noexcept {
    int key = arr[0];
    size_t j = 0;
    while (j > 0 && arr[j - 1] > key) {
        arr[j] = arr[j - 1];
        --j;
    }
    arr[j] = key;
}

// Function for distributing elements into buckets (noexcept for optimization)
void distributeIntoBuckets(const vector<int>& arr, vector<vector<int>>& buckets, int numBuckets, int minVal, int range) noexcept {
    int bucketSize = (range + numBuckets - 1) / numBuckets;
    for (const auto& value : arr) {
        int bucketIndex = (value - minVal) / bucketSize;
        bucketIndex = min(max(bucketIndex, 0), numBuckets - 1);
        buckets[bucketIndex].push_back(value);
    }
}

// Optimized bucket sort function with template unrolling and compile-time calculation
template<size_t Size, int NumBuckets = calculateNumBuckets<Size>()>
void bucketSort(vector<int>& arr) noexcept {
    if (arr.empty()) return;

    if (Size < 16) {
        unrolledInsertionSort<16>(arr, Size);
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
            unrolledInsertionSort<16>(bucket, bucket.size());
        } else {
            sort(bucket.begin(), bucket.end()); // Using std::sort directly
        }
        copy(bucket.begin(), bucket.end(), arr.begin() + index);
        index += bucket.size();
    }
}

// Utility function to print the vector (marked noexcept for optimization)
void printVector(const vector<int>& vec) noexcept {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    const int N = 1000000; // Adjust N for testing
    int modulo = -1;
    vector<int> data(N);
    generate(data.begin(), data.end(), []() { return rand(); });

    if (N <= 30) {
        cout << "Original data:\n";
        printVector(data);
    }

    auto start = chrono::high_resolution_clock::now();

    // Use bucketSort with compile-time optimizations
    bucketSort<N>(data);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    if (N <= 30) {
        cout << "Sorted data:\n";
        printVector(data);
    }
    
    cout << "N = " << prettyNumber(N) << " - Modulo = " << (modulo == -1 ? "no cap " : prettyNumber(modulo)) << endl;
    cout << "Time taken: " << diff.count() << " s\n";
    cout << "Is sorted: " << (is_sorted(data.begin(), data.end()) ? "\033[1;32m[Yes]\033[0m" : "\033[1;31m[No]\033[0m") << endl;

    return 0;
}
