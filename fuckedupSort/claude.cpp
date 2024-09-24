#include <random>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <immintrin.h>
#include <thread>
#include <ctime>
#include <chrono>

using namespace std;

const int INSERTION_SORT_THRESHOLD = 24;
const int PARALLEL_THRESHOLD = 1000000;

template<typename T>
void insertionSort(T* arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template<typename T>
int medianOfThree(T* arr, int left, int mid, int right) {
    if (arr[left] < arr[mid]) {
        if (arr[mid] < arr[right]) return mid;
        else if (arr[left] < arr[right]) return right;
        else return left;
    } else {
        if (arr[left] < arr[right]) return left;
        else if (arr[mid] < arr[right]) return right;
        else return mid;
    }
}

template<typename T>
void heuristicSort(T* arr, int left, int right) {
    while (right - left > INSERTION_SORT_THRESHOLD) {
        int mid = left + ((right - left) >> 1);
        int pivotIndex = medianOfThree(arr, left, mid, right);
        swap(arr[pivotIndex], arr[right]);
        T pivot = arr[right];

        int i = left - 1;
        int j = right;
        while (true) {
            while (arr[++i] < pivot);
            while (j > left && arr[--j] > pivot);
            if (i >= j) break;
            swap(arr[i], arr[j]);
        }
        swap(arr[i], arr[right]);

        int partitionIndex = i;
        if (partitionIndex - left < right - partitionIndex) {
            heuristicSort(arr, left, partitionIndex - 1);
            left = partitionIndex + 1;
        } else {
            heuristicSort(arr, partitionIndex + 1, right);
            right = partitionIndex - 1;
        }
    }

    insertionSort(arr, left, right);
}

template<typename T>
void parallelHeuristicSort(T* arr, int left, int right, int depth = 0) {
    if (right - left <= PARALLEL_THRESHOLD || depth > 3) {
        heuristicSort(arr, left, right);
        return;
    }

    int mid = left + ((right - left) >> 1);
    int pivotIndex = medianOfThree(arr, left, mid, right);
    swap(arr[pivotIndex], arr[right]);
    T pivot = arr[right];

    int i = left - 1;
    int j = right;
    while (true) {
        while (arr[++i] < pivot);
        while (j > left && arr[--j] > pivot);
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[i], arr[right]);

    int partitionIndex = i;
    thread leftThread([&]() {
        parallelHeuristicSort(arr, left, partitionIndex - 1, depth + 1);
    });
    parallelHeuristicSort(arr, partitionIndex + 1, right, depth + 1);
    leftThread.join();
}

template<typename T>
void fastHeuristicSort(vector<T>& arr) {
    if (arr.size() > 1) {
        // Use a better random number generator
        random_device rd;
        mt19937 g(rd());
        shuffle(arr.begin(), arr.end(), g);

        // Use parallel sorting for large arrays
        if (arr.size() > PARALLEL_THRESHOLD) {
            parallelHeuristicSort(arr.data(), 0, arr.size() - 1);
        } else {
            heuristicSort(arr.data(), 0, arr.size() - 1);
        }
    }
}

// Specialization for integers using radix sort
template<>
void fastHeuristicSort<int>(vector<int>& arr) {
    if (arr.size() <= 1) return;

    const int BITS = 8;
    const int BUCKETS = 1 << BITS;
    const int MASK = BUCKETS - 1;

    vector<int> output(arr.size());
    vector<int> count(BUCKETS);

    for (int shift = 0; shift < 32; shift += BITS) {
        fill(count.begin(), count.end(), 0);

        for (int i = 0; i < arr.size(); ++i) {
            ++count[(arr[i] >> shift) & MASK];
        }

        for (int i = 1; i < BUCKETS; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = arr.size() - 1; i >= 0; --i) {
            output[--count[(arr[i] >> shift) & MASK]] = arr[i];
        }

        swap(arr, output);
    }

    // Handle negative numbers
    int split = 0;
    while (split < arr.size() && arr[split] < 0) ++split;
    reverse(arr.begin(), arr.begin() + split);
    reverse(arr.begin() + split, arr.end());
    reverse(arr.begin(), arr.end());
}

int main() {
    const int SIZE = 100000000;
    vector<int> largeVector(SIZE);

    // Fill the vector with random numbers
    srand(time(nullptr));
    for (int i = 0; i < SIZE; ++i) {
        largeVector[i] = rand();
    }

    auto t1 = chrono::high_resolution_clock::now();
    // Sort the vector
    fastHeuristicSort(largeVector);

    auto t2 = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = t2 - t1;

    cout<<"Time taken: "<<duration.count()<<endl;

    //check if the vector is sorted print green couloured yes else print red coloured no use is_sorted function
    if(is_sorted(largeVector.begin(), largeVector.end()))
    {
        cout<<"\033[1;32mYes\033[0m"<<endl;
    }
    else
    {
        cout<<"\033[1;31mNo\033[0m"<<endl;
    }
    return 0;
}