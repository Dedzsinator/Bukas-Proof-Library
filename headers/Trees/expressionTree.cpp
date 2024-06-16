#pragma once

#include "narySearchTree.hpp"

template<typename T>
class ExpressionTree : public NarySearchTree<T> {
  private:
    // Node structure
    struct Node {
      T data;
      Node* parent;
      Node* left;
      Node* right;
    };

    // Root node
    Node* root;

    // Helper functions
    void clear(Node* node);

  public:
    // Constructor
    ExpressionTree();

    // Destructor
    ~ExpressionTree();

    // Clear tree
    void clear();
};
