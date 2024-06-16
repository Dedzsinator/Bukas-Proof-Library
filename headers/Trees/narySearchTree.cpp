#pragma once

#include "naryTree.cpp"

template <typename T>
class NarySearchTree : public NaryTree<T> {
private:
    using Node = typename NaryTree<T>::Node;

    Node* root;

    void insert(Node* node, const T& data) {
        if (data < node->data) {
            if (node->firstChild == nullptr) {
                node->firstChild = new Node{data, node, nullptr, nullptr};
            } else {
                insert(node->firstChild, data);
            }
        } else {
            if (node->nextSibling == nullptr) {
                node->nextSibling = new Node{data, node->parent, nullptr, nullptr};
            } else {
                insert(node->nextSibling, data);
            }
        }
    }

    void remove(Node* node, const T& data) {
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

    bool search(Node* node, const T& data) const {
        if (node == nullptr) {
            return false;
        }

        if (node->data == data) {
            return true;
        }

        return search(node->firstChild, data) || search(node->nextSibling, data);
    }

    void print(Node* node, int depth) const {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }

        std::cout << node->data << std::endl;

        print(node->firstChild, depth + 1);
        print(node->nextSibling, depth);
    }

    Node* search(Node* node, const T& data) {
        if (node == nullptr || node->data == data) {
            return node;
        }

        if (data < node->data) {
            return search(node->firstChild, data);
        } else {
            return search(node->nextSibling, data);
        }
    }

    Node* findMin(Node* node) {
        while (node->firstChild != nullptr) {
            node = node->firstChild;
        }

        return node;
    }

    Node* findMax(Node* node) {
        while (node->nextSibling != nullptr) {
            node = node->nextSibling;
        }

        return node;
    }

    Node* findSuccessor(Node* node) {
        if (node->nextSibling != nullptr) {
            return findMin(node->nextSibling);
        }

        Node* parent = node->parent;
        while (parent != nullptr && node == parent->nextSibling) {
            node = parent;
            parent = parent->parent;
        }

        return parent;
    }

    Node* findPredecessor(Node* node) {
        if (node->firstChild != nullptr) {
            return findMax(node->firstChild);
        }

        Node* parent = node->parent;
        while (parent != nullptr && node == parent->firstChild) {
            node = parent;
            parent = parent->parent;
        }

        return parent;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->firstChild) {
            u->parent->firstChild = v;
        } else {
            u->parent->nextSibling = v;
        }

        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void insertFixup(Node* node) {
        while (node->parent != nullptr && node->parent->data > node->data) {
            if (node == node->parent->firstChild) {
                Node* uncle = node->parent->nextSibling;
                if (uncle != nullptr && uncle->data < node->data) {
                    rotateLeft(node->parent);
                    node = node->nextSibling;
                } else {
                    rotateRight(node);
                    node = node->firstChild;
                }
            } else {
                Node* uncle = node->parent->firstChild;
                if (uncle != nullptr && uncle->data > node->data) {
                    rotateRight(node->parent);
                    node = node->firstChild;
                } else {
                    rotateLeft(node);
                    node = node->nextSibling;
                }
            }
        }

        root = node;
    }

    void removeFixup(Node* node) {
        while (node != root && node->data < node->parent->data) {
            if (node == node->parent->firstChild) {
                Node* sibling = node->parent->nextSibling;
                if (sibling != nullptr && sibling->data > node->data) {
                    rotateRight(node->parent);
                    node = node->nextSibling;
                } else {
                    rotateLeft(node);
                    node = node->firstChild;
                }
            } else {
                Node* sibling = node->parent->firstChild;
                if (sibling != nullptr && sibling->data < node->data) {
                    rotateLeft(node->parent);
                    node = node->firstChild;
                } else {
                    rotateRight(node);
                    node = node->nextSibling;
                }
            }
        }

        root = node;
    }

public:
    NarySearchTree() {
        root = nullptr;
    }

    NarySearchTree(const T& data) {
        root = new Node{data, nullptr, nullptr, nullptr};

        root->parent = nullptr;

        root->firstChild = nullptr;
        root->nextSibling = nullptr;
    }

    ~NarySearchTree() {
        delete root;
    }

    void insert(const T& data) {
        if (root == nullptr) {
            root = new Node{data, nullptr, nullptr, nullptr};
        } else {
            insert(root, data);
        }
    }

    void remove(const T& data) {
        remove(root, data);
    }
    bool search(const T& data) const {
        return search(root, data);
    }

    bool empty() const {
        return root == nullptr;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const NarySearchTree<U>& tree) {
        tree.print(tree.root, 0);
        return os;
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, NarySearchTree<U>& tree) {
        U data;
        is >> data;
        tree.insert(data);
        return is;
    }

    template <typename U>
    friend bool operator==(const NarySearchTree<U>& lhs, const NarySearchTree<U>& rhs) {
        return lhs.root == rhs.root;
    }

    template<typename U>
    friend bool operator!=(const NarySearchTree<U>& lhs, const NarySearchTree<U>& rhs) {
        return !(lhs == rhs);
    }
};
