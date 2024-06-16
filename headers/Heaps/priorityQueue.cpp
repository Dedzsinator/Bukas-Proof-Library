#pragma once

#include "k-aryHeap.hpp"

template <typename T>
class priorityQueue : public k_aryHeap<T, 2> {
  private:
    void heapify(int i);

  public:
    priorityQueue(int capacity);
    ~priorityQueue();

    void insert(T key);

    T extractMax();

    void increaseKey(int i, T key);

    void deleteKey(int i);

    void buildHeap();

    void heapify(int i, int n);

    void heapify();
};
