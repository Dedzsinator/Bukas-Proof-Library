#pragma once

#include "k-aryHeap.cpp"
#include <functional>
#include <iostream>
#include <climits>

template <typename T, typename Comparator = std::less<T>>
class binaryHeap : public k_aryHeap<T, 2, Comparator> {
  private:
    Comparator comp;

    void heapify(int i) {
        int l = this->left(i);
        int r = this->right(i);
        int largest = i;
        if (l < this->size && comp(this->heap[largest], this->heap[l])) {
            largest = l;
        }
        if (r < this->size && comp(this->heap[largest], this->heap[r])) {
            largest = r;
        }
        if (largest != i) {
            std::swap(this->heap[i], this->heap[largest]);
            heapify(largest);
        }
    }

  public:
    binaryHeap(int capacity, Comparator comp = Comparator()) : k_aryHeap<T, 2, Comparator>(capacity, comp), comp(comp) {}

    void insert(T key) {
        if (this->size == this->capacity) {
            std::cout << "Heap is full" << std::endl;
            return;
        }

        this->size++;
        int i = this->size - 1;
        this->heap[i] = key;
        while (i != 0 && comp(this->heap[this->parent(i)], this->heap[i])) {
            std::swap(this->heap[i], this->heap[this->parent(i)]);
            i = this->parent(i);
        }
    }

    T extractTop() {
        if (this->size <= 0) {
            return -1; // or throw an exception
        }

        if (this->size == 1) {
            this->size--;
            return this->heap[0];
        }

        T root = this->heap[0];
        this->heap[0] = this->heap[this->size - 1];
        this->size--;
        heapify(0);

        return root;
    }

    T extractKthTop(int k) {
        if (k > this->size) {
            return -1;
        }

        T top = comp(T(), T()) ? INT_MAX : INT_MIN;
        for (int i = 0; i < k; i++) {
            top = extractTop();
        }

        return top;
    }

    void increaseKey(int i, T key) {
        this->heap[i] = key;
        while (i != 0 && comp(this->heap[this->parent(i)], this->heap[i])) {
            std::swap(this->heap[i], this->heap[this->parent(i)]);
            i = this->parent(i);
        }
    }

    void deleteKey(int i) {
        increaseKey(i, comp(T(), T()) ? INT_MIN : INT_MAX);
        extractTop();
    }
};