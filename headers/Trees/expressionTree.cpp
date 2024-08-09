#pragma once

#include "k-arySearchTree.cpp"
#include <iostream>

template<typename T>
class ExpressionTree {
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
    void clear(Node* node) {
      if (node == nullptr) {
        return;
      }

      clear(node->left);
      clear(node->right);

      delete node;
    }

    void print(Node* node, int level) const {
      if (node == nullptr) {
        return;
      }

      print(node->right, level + 1);

      for (int i = 0; i < level; i++) {
        std::cout << "   ";
      }

      std::cout << node->data << std::endl;

      print(node->left, level + 1);
    }

  public:
    // Constructor
    ExpressionTree() {
      root = nullptr;
    }

    // Destructor
    ~ExpressionTree() {
      clear();
    }

    // Clear tree
    void clear() {
      clear(root);
      root = nullptr;
    }

    // Insert data
    void insert(const T& data) {
      if (root == nullptr) {
        root = new Node{data, nullptr, nullptr, nullptr};
      } else {
        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
          parent = current;

          if (data < current->data) {
            current = current->left;
          } else {
            current = current->right;
          }
        }

        if (data < parent->data) {
          parent->left = new Node{data, parent, nullptr, nullptr};
        } else {
          parent->right = new Node{data, parent, nullptr, nullptr};
        }
      }
    }

    // Remove data
    void remove(const T& data) {
      Node* current = root;

      while (current != nullptr) {
        if (data < current->data) {
          current = current->left;
        } else if (data > current->data) {
          current = current->right;
        } else {
          break;
        }
      }

      if (current == nullptr) {
        return;
      }

      if (current->left == nullptr) {
        if (current->right != nullptr) {
          current->right->parent = current->parent;
        }

        if (current == root) {
          root = current->right;
        } else if (current == current->parent->left) {
          current->parent->left = current->right;
        } else {
          current->parent->right = current->right;
        }

        delete current;
      } else if (current->right == nullptr) {
        current->left->parent = current->parent;

        if (current == root) {
          root = current->left;
        } else if (current == current->parent->left) {
          current->parent->left = current->left;
        } else {
          current->parent->right = current->left;
        }

        delete current;
      } else {
        Node* successor = current->right;

        while (successor->left != nullptr) {
          successor = successor->left;
        }

        current->data = successor->data;

        if (successor == successor->parent->left) {
          successor->parent->left = successor->right;
        } else {
          successor->parent->right = successor->right;
        }

        if (successor->right != nullptr) {
          successor->right->parent = successor->parent;
        }

        delete successor;
      }
    }

    // Search data
    bool search(const T& data) const {
      Node* current = root;

      while (current != nullptr) {
        if (data < current->data) {
          current = current->left;
        } else if (data > current->data) {
          current = current->right;
        } else {
          return true;
        }
      }

      return false;
    }

    // Print tree
    void print() const {
      print(root, 0);
    }
};