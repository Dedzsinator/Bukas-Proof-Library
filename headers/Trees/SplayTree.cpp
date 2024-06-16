#pragma once
#include "../../headers/Trees/SplayTree.hpp"

template <typename T>
SplayTree<T>::SplayTree() {
    root = nullptr;
}

template <typename T>
SplayTree<T>::~SplayTree() {
    clear(root);
}

template <typename T>
void SplayTree<T>::insert(const T& value) {
    if (root == nullptr) {
        root = new Node(value);
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;

        if (value < current->value) {
            current = current->left;
        } else if (value > current->value) {
            current = current->right;
        } else {
            return;
        }
    }

    current = new Node(value, parent);

    if (value < parent->value) {
        parent->left = current;
    } else {
        parent->right = current;
    }

    splay(current);
}

template <typename T>
void SplayTree<T>::remove(const T& value) {
    Node* current = root;

    while (current != nullptr) {
        if (value < current->value) {
            current = current->left;
        } else if (value > current->value) {
            current = current->right;
        } else {
            break;
        }
    }

    if (current == nullptr) {
        return;
    }

    splay(current);

    if (current->left == nullptr) {
        root = current->right;
        if (root != nullptr) {
            root->parent = nullptr;
        }
    } else {
        Node* right = current->right;
        root = current->left;
        root->parent = nullptr;

        Node* temp = root;
        while (temp->right != nullptr) {
            temp = temp->right;
        }

        splay(temp);
        root->right = right;
        if (right != nullptr) {
            right->parent = root;
        }
    }

    delete current;
}

template <typename T>
bool SplayTree<T>::find(const T& value) {
    Node* current = root;

    while (current != nullptr) {
        if (value < current->value) {
            current = current->left;
        } else if (value > current->value) {
            current = current->right;
        } else {
            splay(current);
            return true;
        }
    }

    return false;
}

template <typename T>
void SplayTree<T>::print() {
    print(root, 0);
}

template <typename T>
void SplayTree<T>::read() {
    clear(root);
    root = nullptr;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        T value;
        std::cin >> value;
        insert(value);
    }
}

template <typename T>
typename SplayTree<T>::Node* SplayTree<T>::getRoot() {
    return root;
}

template <typename T>
void SplayTree<T>::setRoot(Node* root) {
    this->root = root;
}

template <typename T>
SplayTree<T>& SplayTree<T>::operator=(const SplayTree<T>& other) {
    if (this == &other) {
        return *this;
    }

    clear(root);
    root = nullptr;

    if (other.root != nullptr) {
        root = new Node(other.root->value);
        root->left = other.root->left;
        root->right = other.root->right;
        root->parent = other.root->parent;
    }

    return *this;
}

template <typename T>
std::ostream& SplayTree<T>::operator<<(std::ostream& os) {
    print(root, 0);
    return os;
}

template <typename T>
std::istream& SplayTree<T>::operator>>(std::istream& is) {
    read();
    return is;
}

template <typename T>
void SplayTree<T>::splay(Node* node) {
    while (node->parent != nullptr) {
        if (node->parent->parent == nullptr) {
            if (node->parent->left == node) {
                rotateRight(node->parent);
            } else {
                rotateLeft(node->parent);
            }
        } else if (node->parent->left == node && node->parent->parent->left == node->parent) {
            rotateRight(node->parent->parent);
            rotateRight(node->parent);
        } else if (node->parent->right == node && node->parent->parent->right == node->parent) {
            rotateLeft(node->parent->parent);
            rotateLeft(node->parent);
        } else if (node->parent->left == node && node->parent->parent->right == node->parent) {
            rotateRight(node->parent);
            rotateLeft(node->parent);
        } else {
            rotateLeft(node->parent);
            rotateRight(node->parent);
        }
    }
}

template <typename T>
void SplayTree<T>::rotateLeft(Node* node) {
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

template <typename T>
void SplayTree<T>::rotateRight(Node* node) {
    Node* left = node->left;
    node->left = left->right;

    if (left->right != nullptr) {
        left->right->parent = node;
    }

    left->parent = node->parent;

    if (node->parent == nullptr) {
        root = left;
    } else if (node == node->parent->left) {
        node->parent->left = left;
    } else {
        node->parent->right = left;
    }

    left->right = node;
    node->parent = left;
}

template <typename T>
void SplayTree<T>::prettyPrint(Node* node, int level) {
    if (node == nullptr) {
        return;
    }

    print(node->right, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "   ";
    }

    std::cout << node->value << std::endl;

    print(node->left, level + 1);
}

template <typename T>
void SplayTree<T>::clear(Node* node) {
    if (node == nullptr) {
        return;
    }

    clear(node->left);
    clear(node->right);

    delete node;
}

