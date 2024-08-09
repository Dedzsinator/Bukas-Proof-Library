#pragma once

#include "k-aryHeap.cpp"
#include <functional>
#include <iostream>
#include <climits>

template <typename T, typename Comparator = std::less<T>>
class priorityQueue : public k_aryHeap<T, 2> {
  private:
    Comparator comp;
    T* heap;
    int size;
    int capacity;

    void heapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l < size && comp(heap[largest], heap[l])) {
            largest = l;
        }
        if (r < size && comp(heap[largest], heap[r])) {
            largest = r;
        }
        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }

    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    int parent(int i) { return (i - 1) / 2; }

  public:
    priorityQueue(int capacity, Comparator comp = Comparator()) : comp(comp) {
        this->capacity = capacity;
        size = 0;
        heap = new T[capacity];
    }

    ~priorityQueue() {
        delete[] heap;
    }

    void insert(T key) {
        if (size == capacity) {
            std::cout << "Heap is full" << std::endl;
            return;
        }

        size++;
        int i = size - 1;
        heap[i] = key;
        while (i != 0 && comp(heap[parent(i)], heap[i])) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    T extractTop() {
        if (size <= 0) {
            return -1;
        }

        if (size == 1) {
            size--;
            return heap[0];
        }

        T root = heap[0];
        heap[0] = heap[size - 1];
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
        int l = left(i);
        int r = right(i);

        if (l < n && comp(heap[largest], heap[l])) {
            largest = l;
        }
        if (r < n && comp(heap[largest], heap[r])) {
            largest = r;
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