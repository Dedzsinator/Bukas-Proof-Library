#pragma once

#include "k-arySearchTree.cpp"
#include <iostream>

template <typename T>
class BinarySearchTree {
private:
    using Node = typename NarySearchTree<T>::Node;

    void insert(Node* node, const T& data) {
        if (data < node->data) {
            if (node->left == nullptr) {
                node->left = new Node{data, node, nullptr, nullptr};
            } else {
                insert(node->left, data);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new Node{data, node, nullptr, nullptr};
            } else {
                insert(node->right, data);
            }
        }
    }

    void remove(Node* node, const T& data) {
        if (node == nullptr) return;

        if (data < node->data) {
            remove(node->left, data);
        } else if (data > node->data) {
            remove(node->right, data);
        } else {
            if (node->left == nullptr) {
                transplant(node, node->right);
            } else if (node->right == nullptr) {
                transplant(node, node->left);
            } else {
                Node* successor = findMin(node->right);
                if (successor->parent != node) {
                    transplant(successor, successor->right);
                    successor->right = node->right;
                    successor->right->parent = successor;
                }
                transplant(node, successor);
                successor->left = node->left;
                successor->left->parent = successor;
            }
            delete node;
        }
    }


    bool search(Node* node, const T& data) const {
        if (node == nullptr) return false;
        if (data < node->data) return search(node->left, data);
        if (data > node->data) return search(node->right, data);
        return true;
    }

    void print(Node* node, int depth) const {
        if (node == nullptr) return;
        print(node->right, depth + 1);
        for (int i = 0; i < depth; ++i) std::cout << "   ";
        std::cout << node->data << std::endl;
        print(node->left, depth + 1);
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* findMax(Node* node) {
        while (node->right != nullptr) node = node->right;
        return node;
    }

    Node* findSuccessor(Node* node) {
        if (node->right != nullptr) return findMin(node->right);
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    Node* findPredecessor(Node* node) {
        if (node->left != nullptr) return findMax(node->left);
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->left) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            this->root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void insertFixup(Node* node) {
        // Placeholder for balancing logic if needed
    }

    void removeFixup(Node* node) {
        // Placeholder for balancing logic if needed
    }

public:
    BinarySearchTree() {
        this->root = nullptr;
    }

    BinarySearchTree(const T& data) {
        this->root = new Node{data, nullptr, nullptr, nullptr};
    }

    ~BinarySearchTree() {
        clear();
    }

    void insert(const T& data) {
        if (this->root == nullptr) {
            this->root = new Node{data, nullptr, nullptr, nullptr};
        } else {
            insert(this->root, data);
        }
    }

    void remove(const T& data) {
        remove(this->root, data);
    }

    void print() const {
        print(this->root, 0);
    }

    bool search(const T& data) const {
        return search(this->root, data);
    }

    bool empty() const {
        return this->root == nullptr;
    }

    void clear() {
        while (!empty()) {
            remove(this->root->data);
        }
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree<U>& tree) {
        tree.print(tree.root, 0);
        return os;
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, BinarySearchTree<U>& tree) {
        U data;
        while (is >> data) {
            tree.insert(data);
        }
        return is;
    }

    template <typename U>
    friend bool operator==(const BinarySearchTree<U>& lhs, const BinarySearchTree<U>& rhs) {
        // Implement comparison logic
        return false;
    }

    template<typename U>
    friend bool operator!=(const BinarySearchTree<U>& lhs, const BinarySearchTree<U>& rhs) {
        return !(lhs == rhs);
    }
};
