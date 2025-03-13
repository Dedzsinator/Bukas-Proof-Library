#include "prettynumber.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <cmath>

using namespace std;

void optimizedSort(int* arr, int size) {
    // Use std::sort which is highly optimized
    std::sort(arr, arr + size);
}

void bucketSort(vector<int>& data) {
    int num_buckets = 8;  // Increase number of buckets to reduce workload per bucket
    int N = data.size();
    vector<int*> buckets(num_buckets);
    vector<int> bucket_sizes(num_buckets, 0);

    // Allocate memory for the buckets
    for (int i = 0; i < num_buckets; ++i) {
        buckets[i] = (int*)mmap(nullptr, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    }

    // Determine the range of data
    int max_value = *max_element(data.begin(), data.end());
    int min_value = *min_element(data.begin(), data.end());
    int range = max_value - min_value + 1;

    // Distribute the data into buckets
    for (int num : data) {
        int bucket_idx = (num - min_value) * num_buckets / range;
        bucket_idx = min(bucket_idx, num_buckets - 1); // Prevent out-of-bounds
        buckets[bucket_idx][bucket_sizes[bucket_idx]++] = num;
    }

    // Fork a limited number of processes to sort buckets in parallel
    vector<pid_t> pids(num_buckets);

    for (int i = 0; i < num_buckets; ++i) {
        pids[i] = fork();
        if (pids[i] == 0) {  // Child process
            optimizedSort(buckets[i], bucket_sizes[i]);
            exit(0);  // Child process exits after sorting
        }
    }

    // Parent process waits for all child processes to finish
    for (int i = 0; i < num_buckets; ++i) {
        waitpid(pids[i], nullptr, 0);
    }

    // Copy the sorted data from shared memory back to the original vector
    size_t idx = 0;
    for (int i = 0; i < num_buckets; ++i) {
        std::copy(buckets[i], buckets[i] + bucket_sizes[i], data.begin() + idx);
        idx += bucket_sizes[i];

        // Free the shared memory for each bucket
        munmap(buckets[i], N * sizeof(int));
    }
}

int main() {
    int N = 100000000;  // Large dataset
    int modulo = 1000000;
    vector<int> data(N);
    generate(data.begin(), data.end(), [modulo]() { return rand() % modulo; });

    auto start = chrono::high_resolution_clock::now();
    bucketSort(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    
    cout<< "N = "<< prettyNumber(N) << " - Modulo = " << prettyNumber(modulo) <<endl;
    cout << "Time taken: " << diff.count() << " s\n";
    cout << "Is sorted: " << (is_sorted(data.begin(), data.end()) ? "\033[1;32m[Yes]\033[0m" : "\033[1;31m[No]\033[0m") << endl;

    return 0;
}
