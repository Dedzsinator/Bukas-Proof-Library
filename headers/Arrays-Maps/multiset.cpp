#include <iostream>

template<class T>
class MultiSet {
  private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        size_t count;
    };

    Node* root;
    size_t size;

  public:
    MultiSet();
    MultiSet(const MultiSet<T>& other);
    MultiSet<T>& operator=(const MultiSet<T>& other);
    void insert(const T& value);
    void erase(const T& value);
    size_t count(const T& value);
    size_t get_size();
    ~MultiSet();
};
