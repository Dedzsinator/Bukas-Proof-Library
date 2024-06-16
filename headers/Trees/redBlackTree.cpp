#pragma once

#include "narySearchTree.hpp"

template<typename T>
class RedBlackTree : public NarySearchTree<T> {
  private:
    // Node structure
    struct Node {
      T data;
      Node* parent;
      Node* left;
      Node* right;
      bool isRed;
    };

    // Root node
    Node* root;

    // Helper functions
    void insertFixup(Node* node);
    void removeFixup(Node* node);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void transplant(Node* u, Node* v);
    Node* minimum(Node* node);
    Node* maximum(Node* node);
    Node* search(Node* node, T data);
    void clear(Node* node);

  public:
    // Constructor
    RedBlackTree();

    // Destructor
    ~RedBlackTree();

    // Insert data
    void insert(T data);

    // Remove data
    void remove(T data);

    // Search data
    bool search(T data);

    // Clear tree
    void clear();
};
