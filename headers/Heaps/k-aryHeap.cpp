#pragma once

#include <iostream>

template <typename T, int k>
class k_aryHeap {
  protected:
    T* heap;
    int size;
    int capacity;

    int parent(int i);

    int child(int i, int j);

    void heapify(int i);

  public:
    k_aryHeap(int capacity);
    ~k_aryHeap();

    void insert(T key);

    T extractMax();

    void increaseKey(int i, T key);

    void deleteKey(int i);  

    void print();

    int getSize();

    bool isEmpty();

    T getMax();

    void heapSort();

    void buildHeap();

    void heapify(int i, int n);

    void heapify();

    void heapifyUp(int i);

    void heapifyDown(int i);

    void heapifyDown(int i, int n);

    void heapifyUp(int i, int n);

    void heapifyUp();

    void heapifyDown();

    template <typename U, int l>
    friend std::ostream& operator<<(std::ostream& os, const k_aryHeap<U, l>& heap);

    template <typename U, int l>
    friend std::istream& operator>>(std::istream& is, k_aryHeap<U, l>& heap);
};
