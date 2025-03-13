#include "prettynumber.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include <random>
#include <limits>

using namespace std;

// Function to perform sorting on a vector
void sortVector(vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

// Function to distribute elements into buckets
void distributeIntoBuckets(const vector<int>& arr, vector<vector<int>>& buckets, vector<mutex>& bucketMutex, int numBuckets, int minVal, double range, int start, int end) {
    for (int i = start; i < end; ++i) {
        int value = arr[i];
        int bucketIndex = static_cast<int>((value - minVal) * numBuckets / range);
        bucketIndex = min(max(bucketIndex, 0), numBuckets - 1);

        {
            lock_guard<mutex> lock(bucketMutex[bucketIndex]);
            buckets[bucketIndex].push_back(value);
        }
    }
}

// Parallel bucket sort function with sorting in each bucket
void bucketSort(vector<int>& arr, int numBuckets = 0) {
    if (arr.empty()) return;

    numBuckets = (numBuckets == 0) ? sqrt(arr.size()) : numBuckets;
    vector<vector<int>> buckets(numBuckets);
    vector<mutex> bucketMutex(numBuckets);

    auto [minIt, maxIt] = minmax_element(arr.begin(), arr.end());
    int minVal = *minIt;
    int maxVal = *maxIt;
    double range = static_cast<double>(maxVal - minVal) + 1.0;

    if (range == 1) {
        return;
    }

    unsigned int numThreads = thread::hardware_concurrency();
    vector<future<void>> futures;
    int chunkSize = arr.size() / numThreads;

    for (unsigned int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? arr.size() : (i + 1) * chunkSize;
        futures.push_back(async(launch::async, distributeIntoBuckets, cref(arr), ref(buckets), ref(bucketMutex), numBuckets, minVal, range, start, end));
    }

    for (auto& fut : futures) {
        fut.get();
    }

    // Sort each bucket in parallel
    vector<future<void>> sortFutures;
    for (auto& bucket : buckets) {
        sortFutures.push_back(async(launch::async, sortVector, ref(bucket)));
    }
    for (auto& fut : sortFutures) {
        fut.get();
    }

    // Sequentially merge the sorted buckets
    size_t index = 0;
    for (auto& bucket : buckets) {
        for (int value : bucket) {
            arr[index++] = value;
        }
    }
}

void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Generate a number of random numbers with uniform distribution
    int N = 1000000; // Adjust N for testing
    int modulo = 1000000;
    vector<int> data(N);

    // Using a narrower range of random numbers for better distribution
    generate(data.begin(), data.end(), [&]() { return rand() % modulo; });

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
    
    cout << "N = " << prettyNumber(N) << " - Modulo = " << (modulo == -1 ? "no cap " : prettyNumber(modulo)) << endl;
    cout << "Time taken: " << diff.count() << " s\n";
    cout << "Is sorted: " << (is_sorted(data.begin(), data.end()) ? "\033[1;32m[Yes]\033[0m" : "\033[1;31m[No]\033[0m") << endl;

    return 0;
}
