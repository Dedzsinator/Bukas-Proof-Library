#include <iostream>

template<class T>
class SkipList {
  private:
    struct Node {
        T data;
        Node* next;
        Node* down;
    };

    Node* head;
    size_t size;
    size_t levels;

  public:
    SkipList();
    SkipList(size_t levels);
    SkipList(size_t levels, const T& val);
    SkipList(const SkipList<T>& other);
    SkipList<T>& operator=(const SkipList<T>& other);
    void insert(const T& value);
    void remove(const T& value);
    bool find(const T& value);
    size_t get_size();
    ~SkipList();
};
