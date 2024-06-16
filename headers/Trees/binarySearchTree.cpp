#pragma once

#include "narySearchTree.hpp"

template <typename T>
class BinarySearchTree : public NarySearchTree<T> {
private:
    using Node = typename NarySearchTree<T>::Node;

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

public:
    BinarySearchTree();
    BinarySearchTree(const T& data);
    ~BinarySearchTree();

    void insert(const T& data);
    void remove(const T& data);
    bool search(const T& data) const;

    bool empty() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree<U>& tree);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, BinarySearchTree<U>& tree);

    template <typename U>
    friend bool operator==(const BinarySearchTree<U>& lhs, const BinarySearchTree<U>& rhs);

    template<typename U>
    friend bool operator!=(const BinarySearchTree<U>& lhs, const BinarySearchTree<U>& rhs);

};
