#include <iostream>

template<class T>
class LRUCache {
  private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    Node* head;
    Node* tail;
    size_t size;
    size_t capacity;

  public:
    LRUCache();
    LRUCache(size_t capacity);
    LRUCache(size_t capacity, const T& val);
    LRUCache(const LRUCache<T>& other);
    LRUCache<T>& operator=(const LRUCache<T>& other);
    void insert(const T& value);
    void remove(const T& value);
    bool find(const T& value);
    size_t get_size();
    ~LRUCache();
};
