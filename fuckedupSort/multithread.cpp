#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include <numeric>  // For iota
#include <random>   // For rand

using namespace std;

// Function to perform heap sort on a deque (deque used instead of vector for better locality)
void heapSort(deque<int>& deq) {
    priority_queue<int, vector<int>, greater<int>> minHeap(deq.begin(), deq.end());
    for (size_t index = 0; !minHeap.empty(); ++index) {
        deq[index] = minHeap.top();
        minHeap.pop();
    }
}

// Function to distribute elements into buckets
void distributeIntoBuckets(const vector<int>& arr, vector<deque<int>>& buckets, vector<mutex>& bucketMutex, int numBuckets, int minVal, int range, int start, int end) {
    vector<deque<int>> localBuckets(numBuckets);

    for (int i = start; i < end; ++i) {
        int value = arr[i];
        int bucketIndex = (value - minVal) * numBuckets / range;
        bucketIndex = min(max(bucketIndex, 0), numBuckets - 1);
        localBuckets[bucketIndex].push_back(value);
    }

    // Write local buckets to global buckets with fine-grained locking
    for (int i = 0; i < numBuckets; ++i) {
        unique_lock<mutex> lock(bucketMutex[i]);
        buckets[i].insert(buckets[i].end(), make_move_iterator(localBuckets[i].begin()), make_move_iterator(localBuckets[i].end()));
    }
}

// Parallel bucket sort function with heaps in each bucket
void bucketHeapSort(vector<int>& arr, int numBuckets = 0) {
    if (arr.empty()) return;

    numBuckets = (numBuckets == 0) ? sqrt(arr.size()) : numBuckets;
    vector<deque<int>> buckets(numBuckets);
    vector<mutex> bucketMutex(numBuckets); // Initialize mutexes

    auto [minIt, maxIt] = minmax_element(arr.begin(), arr.end());
    int minVal = *minIt;
    int maxVal = *maxIt;
    int range = maxVal - minVal + 1;

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

    // Parallelize the sorting of buckets
    vector<future<void>> sortFutures;
    for (auto& bucket : buckets) {
        sortFutures.push_back(async(launch::async, heapSort, ref(bucket)));
    }
    for (auto& fut : sortFutures) {
        fut.get();
    }

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
    bucketHeapSort(data);
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
