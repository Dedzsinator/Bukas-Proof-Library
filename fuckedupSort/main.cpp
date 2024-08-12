#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>
#include <numeric>  // For iota

using namespace std;

// Function to perform optimized insertion sort on a vector
void insertionSort(vector<int>& arr) {
    if (arr.empty()) return;

    size_t n = arr.size();
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

// Function to distribute elements into buckets
void distributeIntoBuckets(const vector<int>& arr, vector<vector<int>>& buckets, int numBuckets, int minVal, int range) {
    int bucketSize = (range + numBuckets - 1) / numBuckets; // Ensure bucket size is at least 1
    for (const auto& value : arr) {
        int bucketIndex = (value - minVal) / bucketSize;
        bucketIndex = min(max(bucketIndex, 0), numBuckets - 1);
        buckets[bucketIndex].push_back(value);
    }
}

// Optimized bucket sort function
void bucketSort(vector<int>& arr, int numBuckets = 0) {
    if (arr.empty()) return;

    size_t arrSize = arr.size();
    
    if (arrSize < 16) {
        insertionSort(arr);
        return;
    }

    // Determine the number of buckets to use
    numBuckets = (numBuckets == 0) ? static_cast<int>(sqrt(arrSize)) : numBuckets;
    if (numBuckets <= 0) {
        numBuckets = 1; // Ensure at least one bucket
    }

    vector<vector<int>> buckets(numBuckets);

    // Find the min and max values in the array
    auto [minIt, maxIt] = minmax_element(arr.begin(), arr.end());
    int minVal = *minIt;
    int maxVal = *maxIt;
    int range = maxVal - minVal + 1;

    // Check for zero range
    if (range <= 0) {
        range = 1; // Ensure range is at least 1 to avoid division by zero
    }

    // Distribute elements into buckets
    distributeIntoBuckets(arr, buckets, numBuckets, minVal, range);

    // Sort each bucket
    for (auto& bucket : buckets) {
        if (bucket.size() < 16) {
            insertionSort(bucket);
        } else {
            sort(bucket.begin(), bucket.end()); // Using std::sort directly
        }
    }

    // Concatenate all buckets into the original array
    size_t index = 0;
    for (auto& bucket : buckets) {
        copy(bucket.begin(), bucket.end(), arr.begin() + index);
        index += bucket.size();
    }
}

void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}


int main() {
    // Generate a number of random numbers
    int N = 10000000; // Adjust N for testing
    vector<int> data(N);
    generate(data.begin(), data.end(), []() { return rand(); });

    if (N <= 30) {
        // Print original data
        cout << "Original data:\n";
        printVector(data);
    }

    // Record the time
    auto start = chrono::high_resolution_clock::now();
    bucketSort(data);
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
