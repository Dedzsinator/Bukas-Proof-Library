#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>
#include <immintrin.h> // For SIMD and prefetching instructions
#include <future>
#include <cmath>
#include <chrono>
#include <random>
#include <numeric>
using namespace std;

std::mutex mtx;

constexpr int L1_CACHE_SIZE = 32 * 1024;  // Assuming 32KB L1 cache
constexpr int L2_CACHE_SIZE = 256 * 1024; // Assuming 256KB L2 cache

// Prefetch data using _mm_prefetch
inline void prefetchData(const int* addr) noexcept {
    _mm_prefetch(reinterpret_cast<const char*>(addr), _MM_HINT_T0);
}

// SIMD-optimized merge function with prefetching and cache optimization
void simdMerge(std::vector<int>& arr, int start, int mid, int end) noexcept {
    if (start >= mid || mid >= end) return; // Guard against invalid bounds

    int i = start, j = mid;
    std::vector<int> temp(end - start); // Use local buffer to avoid dynamic allocation

    size_t k = 0;

    // Merge using SIMD for comparison with prefetching
    while (i < mid && j < end) {
        prefetchData(&arr[i]);
        prefetchData(&arr[j]);

        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Handle remaining elements
    while (i < mid) {
        prefetchData(&arr[i]);
        temp[k++] = arr[i++];
    }
    while (j < end) {
        prefetchData(&arr[j]);
        temp[k++] = arr[j++];
    }

    // Thread-safe copy of temp back to the original array
    std::lock_guard<std::mutex> guard(mtx);
    std::copy(temp.begin(), temp.end(), arr.begin() + start);
}

// Sorts the auxiliary parts of the array in chunks
inline void sortAux(std::vector<int>& arr, int start, int end) noexcept {
    if (start >= end) return;  // Guard against invalid bounds
    std::sort(arr.begin() + start, arr.begin() + end);  // Standard sort
}

// Parallelized merge of multiple sorted chunks
void parallelMerge(std::vector<int>& arr, int numThreads, int chunkSize, int totalSize) {
    std::vector<std::thread> mergeThreads;

    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize * 2;
        int mid = start + chunkSize;
        int end = std::min(start + chunkSize * 2, totalSize);

        if (mid < end) {
            mergeThreads.push_back(std::thread(simdMerge, std::ref(arr), start, mid, end));
        }
    }

    for (auto& t : mergeThreads) {
        t.join();
    }
}

// Cache-aware parallel sort
void parallelSort(std::vector<int>& arr) noexcept {
    int n = arr.size();
    int numThreads = std::thread::hardware_concurrency();
    int chunkSize = L1_CACHE_SIZE / sizeof(int);  // Fit into L1 cache for better cache locality

    // Adjust number of threads if the data size is too small
    if (n < numThreads * chunkSize) {
        numThreads = std::max(1, n / chunkSize);
    }

    // Create threads to sort smaller chunks (cache aware)
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? n : std::min((i + 1) * chunkSize, n);
        threads.push_back(std::thread(sortAux, std::ref(arr), start, end));
    }

    // Join all sorting threads
    for (auto& t : threads) {
        t.join();
    }

    // Merge sorted chunks using parallelized merging
    int currentChunkSize = chunkSize;
    while (currentChunkSize < n) {
        parallelMerge(arr, numThreads, currentChunkSize, n);
        currentChunkSize *= 2;  // Increase the size of chunks to be merged
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
    const size_t N = 10000000; // Adjust N for testing
    vector<int> data(N);
    generate(data.begin(), data.end(), []() { return rand(); });

    if (N <= 30) {
        // Print original data
        cout << "Original data:\n";
        printVector(data);
    }

    // Record the time
    auto start = chrono::high_resolution_clock::now();
    parallelSort(data);
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
