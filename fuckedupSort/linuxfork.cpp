#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <unistd.h>   // For fork and exec
#include <sys/wait.h> // For wait

using namespace std;

// Function to perform heap sort on a deque
void heapSort(deque<int>& deq) {
    priority_queue<int, vector<int>, greater<int>> minHeap(deq.begin(), deq.end());
    for (size_t index = 0; !minHeap.empty(); ++index) {
        deq[index] = minHeap.top();
        minHeap.pop();
    }
}

// Function to distribute elements into buckets
void distributeIntoBuckets(const vector<int>& arr, vector<deque<int>>& buckets, int numBuckets, int minVal, int range, int start, int end) {
    vector<deque<int>> localBuckets(numBuckets);

    for (int i = start; i < end; ++i) {
        int value = arr[i];
        int bucketIndex = (value - minVal) * numBuckets / range;
        bucketIndex = min(max(bucketIndex, 0), numBuckets - 1);
        localBuckets[bucketIndex].push_back(value);
    }

    for (int i = 0; i < numBuckets; ++i) {
        buckets[i].insert(buckets[i].end(), make_move_iterator(localBuckets[i].begin()), make_move_iterator(localBuckets[i].end()));
    }
}

// Function to be executed by child processes
void childProcessTask(int taskId, vector<int>& arr, vector<deque<int>>& buckets, int numBuckets, int minVal, int range, int chunkSize) {
    int start = taskId * chunkSize;
    int end = (taskId == numBuckets - 1) ? arr.size() : (taskId + 1) * chunkSize;

    distributeIntoBuckets(arr, buckets, numBuckets, minVal, range, start, end);

    // Exit the child process after task completion
    _exit(0);
}

// Parallel bucket sort function with heaps in each bucket
void bucketHeapSort(vector<int>& arr, int numBuckets = 0) {
    if (arr.empty()) return;

    numBuckets = (numBuckets == 0) ? sqrt(arr.size()) : numBuckets;
    vector<deque<int>> buckets(numBuckets);

    auto [minIt, maxIt] = minmax_element(arr.begin(), arr.end());
    int minVal = *minIt;
    int maxVal = *maxIt;
    int range = maxVal - minVal + 1;

    unsigned int numProcesses = min(static_cast<int>(thread::hardware_concurrency()), numBuckets);
    int chunkSize = arr.size() / numProcesses;

    vector<pid_t> pids;

    // Fork child processes for distributing elements into buckets
    for (unsigned int i = 0; i < numProcesses; ++i) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            childProcessTask(i, arr, buckets, numBuckets, minVal, range, chunkSize);
        } else if (pid > 0) {
            // Parent process
            pids.push_back(pid);
        } else {
            cerr << "Fork failed!" << endl;
            exit(1);
        }
    }

    // Parent process waits for all child processes to finish
    for (pid_t pid : pids) {
        waitpid(pid, nullptr, 0);
    }

    // Sort each bucket (using single-threaded approach)
    for (auto& bucket : buckets) {
        heapSort(bucket);
    }

    // Merge the sorted buckets back into the original array
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
    int N = 1000000; // Adjust N for testing
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
