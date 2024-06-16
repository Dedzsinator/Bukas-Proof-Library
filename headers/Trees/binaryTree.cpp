#pragma once

#include "naryTree.hpp"

template <typename T>
class NarySearchTree : public NaryTree<T> {
private:
    using Node = typename NaryTree<T>::Node;

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
    NarySearchTree();
    NarySearchTree(const T& data);
    ~NarySearchTree();

    void insert(const T& data);
    void remove(const T& data);
    bool search(const T& data) const;

    bool empty() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const NarySearchTree<U>& tree);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, NarySearchTree<U>& tree);

    template <typename U>
    friend bool operator==(const NarySearchTree<U>& lhs, const NarySearchTree<U>& rhs);

    template<typename U>
    friend bool operator!=(const NarySearchTree<U>& lhs, const NarySearchTree<U>& rhs);
};
