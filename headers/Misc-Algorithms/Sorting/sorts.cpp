#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <atomic>
#include <future>
#include <functional>
using namespace std;

template <typename ITERATOR, typename COMPARE = std::less<>>
class Sorts {
  const int RUN = 32;

public:
/*template<typename T>
void swap(ITERATOR a, ITERATOR b) {
  auto temp = *a;
  *a = *b;
  *b = temp;
}*/

Sorts() {}

ITERATOR partition(ITERATOR begin, ITERATOR end, COMPARE comp) {
    auto pivot = *begin;
    ITERATOR left = begin;
    ITERATOR right = end;

    while (true) {
        while (left != right && comp(*left, pivot)) {
            ++left;
        }
        while (left != right && comp(pivot, *right)) {
            --right;
        }
        if (left == right) break;
        std::swap(*left, *right);
    }
    return left;
}

static void heapify(ITERATOR begin, int size, int root, COMPARE comp = COMPARE()) {
  int largest = root;
  int left = 2 * root + 1;
  int right = 2 * root + 2;

  if (left < size && comp(*(begin + left), *(begin + largest))) {
    largest = left;
  }
  if (right < size && comp(*(begin + right), *(begin + largest))) {
    largest = right;
  }
  if (largest != root) {
    std::swap(*(begin + root), *(begin + largest));
    heapify(begin, size, largest, comp);
  }
}

void bubbleSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  bool swapped = true;
  while (swapped) {
    swapped = false;
    for (ITERATOR i = begin; i != end - 1; i++) {
      if (comp(*(i + 1), *i)) {
        std::swap(*i, *(i + 1));
        swapped = true;
      }
    }
  }
}

void merge(ITERATOR begin, ITERATOR middle, ITERATOR end, COMPARE comp) {
    ITERATOR i = begin;
    ITERATOR j = middle;
    
    while (i < j && j < end) {
        if (comp(*j, *i)) {
            std::iter_swap(i, j);
            
            ITERATOR k = j;
            while (k + 1 < end && comp(*(k + 1), *k)) {
                std::iter_swap(k, k + 1);
                ++k;
            }
        }
        ++i;
        if (i == j) j++;
    }
}

void mergeSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
    auto size = static_cast<size_t>(std::distance(begin, end)); 
    if (size > 1) {
        ITERATOR middle = std::next(begin, size / 2);

        const size_t SINGLE_THREAD_THRESHOLD = 1000; 

        if (size > SINGLE_THREAD_THRESHOLD) {
            auto future = std::async(std::launch::async, [this, begin, middle, comp]() {
                this->mergeSort(begin, middle, comp);
            });
            this->mergeSort(middle, end, comp); 
            future.wait(); 
        } else {
            this->mergeSort(begin, middle, comp);
            this->mergeSort(middle, end, comp);
        }

        
        std::inplace_merge(begin, middle, end, comp);
    }
}

static void quickSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  if (static_cast<size_t>(end - begin) > 1) {
    if (static_cast<size_t>(end - begin)) {
      std::sort(begin, end, comp);
    } else {
      
      Sorts<ITERATOR, COMPARE> sorter;
      ITERATOR partitionIndex = sorter.partition(begin, end - 1, comp); 
      quickSort(begin, partitionIndex, comp);
      quickSort(partitionIndex + 1, end, comp);
    }
  }
}

void insertionSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  for (ITERATOR i = begin + 1; i != end; i++) {
    ITERATOR j = i;
    while (j != begin && comp(*j, *(j - 1))) {
      std::swap(*j, *(j - 1));
      j--;
    }
  }
}

void skaSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  //detail::ska_sort(begin, end, comp);
}

void skaCopySort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  //detail::ska_sort_copy(begin, end, comp);
}

void shellSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  auto size = std::distance(begin, end);
  for (int gap = size / 2; gap > 0; gap /= 2) {
    for (ITERATOR i = begin + gap; i != end; i++) {
      ITERATOR j = i;
      while (j >= begin + gap && comp(*j, *(j - gap))) {
        std::swap(*j, *(j - gap));
        j -= gap;
      }
    }
  }
}

//!----------------------------------------------

void introSortHelper(ITERATOR begin, ITERATOR end, int depth, COMPARE comp) {
  if (std::distance(begin, end) <= 1) return;
  if (depth == 0) {
    heapSort(begin, end, comp);
    return;
  }

  ITERATOR partitionIndex = partition(begin, end, comp);
  introSortHelper(begin, partitionIndex, depth - 1, comp);
  introSortHelper(partitionIndex + 1, end, depth - 1, comp);
}

void introSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  auto size = std::distance(begin, end);
  int maxDepth = 2 * static_cast<int>(std::log(size));
  introSortHelper(begin, end, maxDepth, comp);
}

void blockSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  cout<<"W.I.P"<<endl;
}

void smoothSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  cout<<"W.I.P"<<endl;
}

void spagettiSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  cout<<"W.I.P"<<endl;
}

void grailSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  cout<<"W.I.P"<<endl;
}

void americanFlagSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  cout<<"W.I.P"<<endl;
}

void sqrtSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  cout<<"W.I.P"<<endl;
}

void shelfSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  cout<<"W.I.P"<<endl;
}
//!----------------------------------------------

void bucketSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  static_assert(std::is_arithmetic<typename std::iterator_traits<ITERATOR>::value_type>::value,
                "bucketSort requires numeric value types.");

  auto size = std::distance(begin, end);
  if (size <= 1) return;

  int num_buckets = static_cast<int>(std::sqrt(size));
  auto min_val = *std::min_element(begin, end, comp);
  auto max_val = *std::max_element(begin, end, comp);

  
  if (min_val == max_val) return;

  double spread = static_cast<double>(max_val - min_val) / num_buckets;
  using VALTYPE = typename std::iterator_traits<ITERATOR>::value_type;
  std::vector<std::vector<VALTYPE>> buckets(num_buckets);

  for (auto it = begin; it != end; ++it) {
    int bucket_index = std::min(static_cast<int>((static_cast<double>(*it) - min_val) / spread), num_buckets - 1);
    buckets[bucket_index].push_back(*it);
  }

  for (auto& bucket : buckets) {
    std::sort(bucket.begin(), bucket.end(), comp);
  }

  auto it = begin;
  for (auto& bucket : buckets) {
    for (auto value : bucket) {
      *it++ = value;
    }
  }
}

static auto getMax(ITERATOR begin, ITERATOR end) {
        auto maxElement = *begin;
        for (auto it = begin; it != end; ++it) {
            if (*it > maxElement) {
                maxElement = *it;
            }
        }
        return maxElement;
    }
    
    static void countSort(ITERATOR begin, ITERATOR end, int exp = 1) {
        std::vector<typename std::iterator_traits<ITERATOR>::value_type> output(std::distance(begin, end));
        int i, count[10] = {0};

        
        for (auto it = begin; it != end; ++it) {
            count[((*it / exp) % 10)]++;
        }

        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        
        for (auto it = end - 1; ; --it) {
            output[count[((*it / exp) % 10)] - 1] = *it;
            count[((*it / exp) % 10)]--;
            if (it == begin) break;
        }

        std::copy(output.begin(), output.end(), begin);
    }

    static void radixSort(ITERATOR begin, ITERATOR end) {
        
        auto max = getMax(begin, end);

        
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countSort(begin, end, exp);
        }
    }

void magyarSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  cout<<"W.I.P"<<endl; 
}

void heapSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
  auto size = std::distance(begin, end);
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(begin, size, i, comp);
  }
  for (int i = size - 1; i >= 0; i--) {
    std::swap(*begin, *(begin + i));
    heapify(begin, i, 0, comp);
  }
}

void timSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
    int length = std::distance(begin, end);
    for (ITERATOR i = begin; distance(i, end) > 0; i += RUN) {
        insertionSort(i, std::next(i, std::min(RUN, int(std::distance(i, end)))), comp);
    }

    for (int size = RUN; size < length; size = 2*size) {
        for (ITERATOR left = begin; left < end; left += 2*size) {
            ITERATOR mid = left + size <= end ? left + size : end;
            ITERATOR right = left + 2*size <= end ? left + 2*size : end;

            if (mid < right) {
                merge(left, mid, right, comp);
            }
        }
    }
}

void treeSort(ITERATOR begin, ITERATOR end, COMPARE comp = COMPARE()) {
    struct TreeNode {
        typename std::iterator_traits<ITERATOR>::value_type value;
        TreeNode *left = nullptr, *right = nullptr;

        TreeNode(typename std::iterator_traits<ITERATOR>::value_type val) : value(val) {}
    };

    std::function<void(TreeNode*&, typename std::iterator_traits<ITERATOR>::value_type, COMPARE&)> insert;
    insert = [&](TreeNode*& root, typename std::iterator_traits<ITERATOR>::value_type val, COMPARE& comp) mutable {
        if (!root) root = new TreeNode(val);
        else if (comp(val, root->value)) insert(root->left, val, comp);
        else insert(root->right, val, comp);
    };

    std::function<void(TreeNode*, ITERATOR&)> inOrder;
    inOrder = [&](TreeNode* node, ITERATOR& iter) mutable {
        if (!node) return;
        inOrder(node->left, iter);
        *iter++ = node->value;
        inOrder(node->right, iter);
    };

    TreeNode* root = nullptr;
    for (auto it = begin; it != end; ++it) {
        insert(root, *it, comp);
    }

    inOrder(root, begin);
}
};