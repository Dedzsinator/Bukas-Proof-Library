#pragma once

#include <iostream>

template <typename T>
class NaryTree {
protected:
    struct Node {
        T data;
        Node* parent;
        Node* firstChild;
        Node* nextSibling;
    };

    Node* root;
   
public: 
    virtual Node* getNode(Node* node, const T& data) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->data == data) {
            return node;
        }

        Node* found = getNode(node->firstChild, data);
        if (found != nullptr) {
            return found;
        }

        return getNode(node->nextSibling, data);
    }

    virtual void fancyPrint(Node* node, int depth) const {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }

        std::cout << node->data << std::endl;

        fancyPrint(node->firstChild, depth + 1);
        fancyPrint(node->nextSibling, depth);
    }

    virtual void insert(Node* node, const T& data) {
        if (node->firstChild == nullptr) {
            node->firstChild = new Node{data, node, nullptr, nullptr};
        } else {
            insert(node->firstChild, data);
        }
    }

    virtual void remove(Node* node, const T& data) {
        Node* toRemove = search(node, data);

        if (toRemove == nullptr) {
            return;
        }

        if (toRemove->firstChild == nullptr) {
            transplant(toRemove, toRemove->nextSibling);
        } else if (toRemove->nextSibling == nullptr) {
            transplant(toRemove, toRemove->firstChild);
        } else {
            Node* successor = findSuccessor(toRemove);
            if (successor->parent != toRemove) {
                transplant(successor, successor->nextSibling);
                successor->nextSibling = toRemove->nextSibling;
                successor->nextSibling->parent = successor;
            }
            transplant(toRemove, successor);
            successor->firstChild = toRemove->firstChild;
            successor->firstChild->parent = successor;
        }

        delete toRemove;
    }

    virtual bool search(Node* node, const T& data) const {
        if (node == nullptr) {
            return false;
        }

        if (node->data == data) {
            return true;
        }

        return search(node->firstChild, data) || search(node->nextSibling, data);
    }

    virtual void print(Node* node, int depth) const {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }

        std::cout << node->data << std::endl;

        print(node->firstChild, depth + 1);
        print(node->nextSibling, depth);
    
    }

public:
    NaryTree() {
        root = nullptr;
    }

    NaryTree(const T& data) {
        root = new Node{data, nullptr, nullptr, nullptr};
    }

    virtual ~NaryTree() {
        delete root;
    }

    virtual void insert(const T& data) {
        if (root == nullptr) {
            root = new Node{data, nullptr, nullptr, nullptr};
        } else {
            insert(root, data);
        }
    }

    virtual void remove(const T& data) {
        remove(root, data);
    }
    
    virtual bool search(const T& data) const {
        return search(root, data);
    }

    virtual bool empty() const {
        return root == nullptr;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const NaryTree<U>& tree) {
        tree.print(tree.root, 0);
        return os;
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, NaryTree<U>& tree) {
        U data;
        is >> data;
        tree.insert(data);
        return is;
    }

    template <typename U>
    friend bool operator==(const NaryTree<U>& lhs, const NaryTree<U>& rhs) {
        return compare(lhs.root, rhs.root);
    }

    template<typename U>
    friend bool operator!=(const NaryTree<U>& lhs, const NaryTree<U>& rhs) {
        return !(lhs == rhs);
    }
};
