#pragma once

#include "k-aryHeap.hpp"

template <typename T>
class binaryHeap : public k_aryHeap<T, 2> {
  private:
    void heapify(int i);

  public:
    binaryHeap(int capacity);
    ~binaryHeap();

    void insert(T key);

    T extractMax();

    void increaseKey(int i, T key);

    void deleteKey(int i);
}
