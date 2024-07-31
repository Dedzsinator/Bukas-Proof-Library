#include <iostream>

using namespace std;

template <typename T>
class BTree : public NaryTree<T> {
private:
    using Node = typename NaryTree<T>::Node;

public:
    void insert(Node* node, const T& data);
    void remove(Node* node, const T& data);
    bool search(Node* node, const T& data) const;

    void print(Node* node, int depth) const;

    Node* search(Node* node, const T& data);

    Node* findMin(Node* node);

    Node* findMax(Node* node);

    Node* findSuccessor(Node* node);

    Node* findPredecessor(Node* node);

    void transplant(Node* u, Node* v);

    void insertFixup(Node* node);

    void removeFixup(Node* node);
};