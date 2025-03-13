#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <chrono>
#include <queue>
#include <numeric>
#include <cstdlib> // For std::rand()
#include "prettynumber.cpp"

using namespace std;

// Merge function to merge multiple sorted arrays efficiently
vector<int> mergeSortedArrays(vector<vector<int>>& arrays) {
    struct QueueEntry {
        vector<int>::iterator it;
        vector<int>::iterator end;
    };

    auto compare = [](const QueueEntry& a, const QueueEntry& b) {
        return *(a.it) > *(b.it);
    };

    priority_queue<QueueEntry, vector<QueueEntry>, decltype(compare)> minHeap(compare);

    vector<int> result;
    // Reserve space for the result vector based on the total number of elements
    result.reserve(accumulate(arrays.begin(), arrays.end(), size_t(0), [](size_t sum, const vector<int>& v) {
        return sum + v.size();
    }));

    for (auto& array : arrays) {
        if (!array.empty()) {
            minHeap.push({array.begin(), array.end()});
        }
    }

    while (!minHeap.empty()) {
        auto top = minHeap.top();
        minHeap.pop();
        result.push_back(*(top.it));
        if (++top.it != top.end) {
            minHeap.push(top);
        }
    }

    return result;
}

// Function to sort a chunk
vector<int> sortChunk(vector<int> chunk) {
    sort(chunk.begin(), chunk.end());
    return chunk;
}

// Function to parallelize the sorting process
vector<int> parallelSort(vector<int>& arr, size_t threshold = 1000) {
    int n = arr.size();
    if (n <= 1) return arr;

    vector<vector<int>> subarrays;
    vector<int> current_chunk;
    current_chunk.reserve(threshold);

    for (int i = 0; i < n; ++i) {
        if (current_chunk.size() >= threshold) {
            subarrays.push_back(current_chunk);
            current_chunk.clear();
        }
        current_chunk.push_back(arr[i]);
    }

    if (!current_chunk.empty()) {
        subarrays.push_back(current_chunk);
    }

    // Sort each chunk in parallel
    vector<future<vector<int>>> futures;
    for (auto& chunk : subarrays) {
        futures.push_back(async(launch::async, sortChunk, std::move(chunk)));
    }

    vector<vector<int>> sorted_chunks;
    for (auto& fut : futures) {
        sorted_chunks.push_back(fut.get());
    }

    // Merge all sorted chunks
    return mergeSortedArrays(sorted_chunks);
}

// Inline function to print a vector
inline void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    //if no args are passed set N to 10 million
    if (argc == 1) {
        argc = 2;
        argv[1] = "10000000";
    }

    size_t N = stoi(argv[1]);

    int modulo = -1;

    // Generate random numbers
    vector<int> data(N);
    generate(data.begin(), data.end(), []() { return rand(); });

    auto start = chrono::high_resolution_clock::now();
    vector<int> res = parallelSort(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    /* Print time taken for bench.py
    cout<< "N = " << prettyNumber(N)<<endl;
    cout << diff.count() << endl;
    */

    cout << "N = " << prettyNumber(N) << " - Modulo = " << (modulo == -1 ? "no cap " : prettyNumber(modulo)) << endl;
    cout << "Time taken: " << diff.count() << " s\n";
    cout << "Is sorted: " << (is_sorted(res.begin(), res.end()) ? "\033[1;32m[Yes]\033[0m" : "\033[1;31m[No]\033[0m") << endl;
    return 0;
}
