#pragma once

#include "k-arySearchTree.cpp"

template<typename T>
class RedBlackTree {
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
    void insertFixup(Node* node) {
      while (node != root && node->parent->isRed) {
        if (node->parent == node->parent->parent->left) {
          Node* uncle = node->parent->parent->right;
          if (uncle->isRed) {
            node->parent->isRed = false;
            uncle->isRed = false;
            node->parent->parent->isRed = true;
            node = node->parent->parent;
          } else {
            if (node == node->parent->right) {
              node = node->parent;
              rotateLeft(node);
            }
            node->parent->isRed = false;
            node->parent->parent->isRed = true;
            rotateRight(node->parent->parent);
          }
        } else {
          Node* uncle = node->parent->parent->left;
          if (uncle->isRed) {
            node->parent->isRed = false;
            uncle->isRed = false;
            node->parent->parent->isRed = true;
            node = node->parent->parent;
          } else {
            if (node == node->parent->left) {
              node = node->parent;
              rotateRight(node);
            }
            node->parent->isRed = false;
            node->parent->parent->isRed = true;
            rotateLeft(node->parent->parent);
          }
        }
      }
      root->isRed = false;
    }

    void removeFixup(Node* node) {
      while (node != root && !node->isRed) {
        if (node == node->parent->left) {
          Node* sibling = node->parent->right;
          if (sibling->isRed) {
            sibling->isRed = false;
            node->parent->isRed = true;
            rotateLeft(node->parent);
            sibling = node->parent->right;
          }
          if (!sibling->left->isRed && !sibling->right->isRed) {
            sibling->isRed = true;
            node = node->parent;
          } else {
            if (!sibling->right->isRed) {
              sibling->left->isRed = false;
              sibling->isRed = true;
              rotateRight(sibling);
              sibling = node->parent->right;
            }
            sibling->isRed = node->parent->isRed;
            node->parent->isRed = false;
            sibling->right->isRed = false;
            rotateLeft(node->parent);
            node = root;
          }
        } else {
          Node* sibling = node->parent->left;
          if (sibling->isRed) {
            sibling->isRed = false;
            node->parent->isRed = true;
            rotateRight(node->parent);
            sibling = node->parent->left;
          }
          if (!sibling->right->isRed && !sibling->left->isRed) {
            sibling->isRed = true;
            node = node->parent;
          } else {
            if (!sibling->left->isRed) {
              sibling->right->isRed = false;
              sibling->isRed = true;
              rotateLeft(sibling);
              sibling = node->parent->left;
            }
            sibling->isRed = node->parent->isRed;
            node->parent->isRed = false;
            sibling->left->isRed = false;
            rotateRight(node->parent);
            node = root;
          }
        }
      }
      node->isRed = false;
    }

    void rotateLeft(Node* node) {
      Node* right = node->right;
      node->right = right->left;
      if (right->left != nullptr) {
        right->left->parent = node;
      }
      right->parent = node->parent;
      if (node->parent == nullptr) {
        root = right;
      } else if (node == node->parent->left) {
        node->parent->left = right;
      } else {
        node->parent->right = right;
      }
      right->left = node;
      node->parent = right;
    }

    void rotateRight(Node* node) {
      Node* left = node->left;
      node->left = left->right;
      if (left->right != nullptr) {
        left->right->parent = node;
      }
      left->parent = node->parent;
      if (node->parent == nullptr) {
        root = left;
      } else if (node == node->parent->right) {
        node->parent->right = left;
      } else {
        node->parent->left = left;
      }
      left->right = node;
      node->parent = left;
    }

    void transplant(Node* u, Node* v) {
      if (u->parent == nullptr) {
        root = v;
      } else if (u == u->parent->left) {
        u->parent->left = v;
      } else {
        u->parent->right = v;
      }
      v->parent = u->parent;
    }

    Node* minimum(Node* node) {
      while (node->left != nullptr) {
        node = node->left;
      }
      return node;
    }

    Node* maximum(Node* node) {
      while (node->right != nullptr) {
        node = node->right;
      }
      return node;
    }

    Node* search(Node* node, T data) {
      if (node == nullptr || node->data == data) {
        return node;
      }

      if (data < node->data) {
        return search(node->left, data);
      } else {
        return search(node->right, data);
      }
    }

    void clear(Node* node) {
      if (node == nullptr) {
        return;
      }

      clear(node->left);
      clear(node->right);
      delete node;
    }

  public:
    // Constructor
    RedBlackTree() {
      root = nullptr;
    }

    // Destructor
    ~RedBlackTree() {
      clear();
    }

    void print(Node* node, int level) const {
      if (node == nullptr) {
        return;
      }

      print(node->right, level + 1);
      for (int i = 0; i < level; i++) {
        cout << "    ";
      }
      cout << node->data << endl;
      print(node->left, level + 1);
    }

    void print() const {
      print(root, 0);
    }

    // Insert data
    void insert(T data) {
      Node* node = new Node{data, nullptr, nullptr, nullptr, true};
      Node* parent = nullptr;
      Node* current = root;
      while (current != nullptr) {
        parent = current;
        if (node->data < current->data) {
          current = current->left;
        } else {
          current = current->right;
        }
      }
      node->parent = parent;
      if (parent == nullptr) {
        root = node;
      } else if (node->data < parent->data) {
        parent->left = node;
      } else {
        parent->right = node;
      }
      insertFixup(node);
    }

    // Remove data
    void remove(T data) {
      Node* node = search(root, data);
      if (node == nullptr) {
        return;
      }
      Node* toRemove = node;
      bool isRed = toRemove->isRed;
      Node* successor = nullptr;
      if (node->left == nullptr) {
        successor = node->right;
        transplant(node, node->right);
      } else if (node->right == nullptr) {
        successor = node->left;
        transplant(node, node->left);
      } else {
        toRemove = minimum(node->right);
        isRed = toRemove->isRed;
        successor = toRemove->right;
        if (toRemove->parent == node) {
          successor->parent = toRemove;
        } else {
          transplant(toRemove, toRemove->right);
          toRemove->right = node->right;
          toRemove->right->parent = toRemove;
        }
        transplant(node, toRemove);
        toRemove->left = node->left;
        toRemove->left->parent = toRemove;
        toRemove->isRed = node->isRed;
      }
      if (!isRed) {
        removeFixup(successor);
      }
      delete node;
    }

    // Search data
    bool search(T data) {
      return search(root, data) != nullptr;
    }

    // Clear tree
    void clear() {
      clear(root);
      root = nullptr;
    }
};
