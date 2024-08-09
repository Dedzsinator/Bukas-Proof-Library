#pragma once

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class fibonacciHeap {
protected:
    struct Node {
        T key;
        int degree;
        bool mark;
        Node* parent;
        Node* child;
        Node* left;
        Node* right;
    };

    Node* min;
    int n;
    vector<Node*> nodes;

    void consolidate() {
        int maxDegree = 0;
        for (auto node : nodes) {
            if (node->degree > maxDegree) {
                maxDegree = node->degree;
            }
        }

        vector<Node*> A(maxDegree + 1, nullptr);
        Node* start = min;
        Node* w = min;
        do {
            Node* x = w;
            w = w->right;
            int d = x->degree;
            while (A[d]) {
                Node* y = A[d];
                if (x->key > y->key) {
                    Node* temp = x;
                    x = y;
                    y = temp;
                }
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        } while (w != start);

        min = nullptr;
        for (auto node : nodes) {
            if (node) {
                if (!min) {
                    min = node;
                } else {
                    if (node->key < min->key) {
                        min = node;
                    }
                }
            }
        }
    }

    void link(Node* y, Node* x) {
        y->left->right = y->right;
        y->right->left = y->left;

        if (!x->child) {
            x->child = y;
            y->left = y;
            y->right = y;
        } else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right = y;
            y->right->left = y;
        }

        y->parent = x;
        x->degree++;
        y->mark = false;
    }

    void cut(Node* x, Node* y) {
        if (x == x->right) {
            y->child = nullptr;
        } else {
            x->left->right = x->right;
            x->right->left = x->left;
            if (y->child == x) {
                y->child = x->right;
            }
        }

        y->degree--;
        x->left = min;
        x->right = min->right;
        min->right = x;
        x->right->left = x;
        x->parent = nullptr;
        x->mark = false;
    }

    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z) {
            if (!y->mark) {
                y->mark = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

public:
    fibonacciHeap() {
        min = nullptr;
        n = 0;
    }

    ~fibonacciHeap() {
        for (auto node : nodes) {
            delete node;
        }
    }

    void insert(T key) {
        Node* x = new Node();
        x->key = key;
        x->degree = 0;
        x->mark = false;
        x->parent = nullptr;
        x->child = nullptr;
        x->left = x;
        x->right = x;

        if (min) {
            x->left = min;
            x->right = min->right;
            min->right = x;
            x->right->left = x;
            if (x->key < min->key) {
                min = x;
            }
        } else {
            min = x;
        }

        n++;
    }

    T extractMin() {
        if (isEmpty()) {
            cout << "Heap is empty\n";
            return numeric_limits<T>::max();
        }

        Node* z = min;
        if (z->child) {
            Node* x = z->child;
            do {
                Node* next = x->right;
                nodes.push_back(x);
                x->parent = nullptr;
                x = next;
            } while (x != z->child);
        }

        if (z == z->right) {
            min = nullptr;
        } else {
            min = z->right;
            consolidate();
        }

        n--;
        return z->key;
    }

    void decreaseKey(Node* x, T key) {
        if (key > x->key) {
            cout << "New key is greater than current key\n";
            return;
        }

        x->key = key;
        Node* y = x->parent;
        if (y && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }

        if (x->key < min->key) {
            min = x;
        }
    }

    void deleteNode(Node* x) {
        decreaseKey(x, numeric_limits<T>::min());
        extractMin();
    }

    void print() {
        cout << *this;
    }

    int getSize() {
        return n;
    }

    bool isEmpty() {
        return n == 0;
    }

    T getMin() {
        return min->key;
    }

    template <typename U>
    friend ostream& operator<<(ostream& os, const fibonacciHeap<U>& heap) {
        if (heap.isEmpty()) {
            os << "Empty heap\n";
            return os;
        }
    
        os << "Heap:\n";
        for (auto node : heap.nodes) {
            os << "Node " << node->key << ":\n";
            os << "  Parent: " << (node->parent ? to_string(node->parent->key) : "NULL") << "\n";
            os << "  Child: " << (node->child ? to_string(node->child->key) : "NULL") << "\n";
            os << "  Left: " << (node->left ? to_string(node->left->key) : "NULL") << "\n";
            os << "  Right: " << (node->right ? to_string(node->right->key) : "NULL") << "\n";
            os << "  Degree: " << node->degree << "\n";
            os << "  Mark: " << node->mark << "\n";
        }
    
        return os;
    }
};