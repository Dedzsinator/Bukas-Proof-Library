#pragma once

#include <vector>
#include <functional>
#include <iostream>
#include <climits>

template <typename T, int K = 2, typename Comparator = std::less<T>>
class k_aryHeap {
  private:
    Comparator comp;
    std::vector<T> heap;
    int size;

    void heapify(int i) {
        int largest = i;
        for (int j = 1; j <= K; ++j) {
            int child = K * i + j;
            if (child < size && comp(heap[largest], heap[child])) {
                largest = child;
            }
        }
        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }

    int parent(int i) { return (i - 1) / K; }

  public:
    k_aryHeap(int capacity, Comparator comp = Comparator()) : comp(comp), size(0) {
        heap.reserve(capacity);
    }

    void insert(T key) {
        if (size == heap.capacity()) {
            std::cout << "Heap is full" << std::endl;
            return;
        }

        heap.push_back(key);
        size++;
        int i = size - 1;
        while (i != 0 && comp(heap[parent(i)], heap[i])) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    T extractTop() {
        if (size <= 0) {
            return -1; // or throw an exception
        }

        if (size == 1) {
            size--;
            T root = heap.back();
            heap.pop_back();
            return root;
        }

        T root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        size--;
        heapify(0);
        return root;
    }

    void increaseKey(int i, T key) {
        heap[i] = key;
        while (i != 0 && comp(heap[parent(i)], heap[i])) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void deleteKey(int i) {
        increaseKey(i, comp(T(), T()) ? INT_MIN : INT_MAX);
        extractTop();
    }

    void buildHeap() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    void heapify(int i, int n) {
        int largest = i;
        for (int j = 1; j <= K; ++j) {
            int child = K * i + j;
            if (child < n && comp(heap[largest], heap[child])) {
                largest = child;
            }
        }
        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapify(largest, n);
        }
    }

    void heapify() {
        heapify(0, size);
    }
};
