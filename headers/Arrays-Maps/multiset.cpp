#include <iostream>
#include <functional>  // for std::function
#include <utility>

template <typename T>
class Multiset {
private:
    struct Node {
        T data;
        size_t count;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t size_;

    void insert(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
        } else if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        } else {
            ++node->count;
        }
    }

    void erase(Node*& node, const T& value) {
        if (!node) return;

        if (value < node->data) {
            erase(node->left, value);
        } else if (value > node->data) {
            erase(node->right, value);
        } else {
            if (node->count > 1) {
                --node->count;
            } else {
                Node* oldNode = node;
                if (!node->left) {
                    node = node->right;
                } else if (!node->right) {
                    node = node->left;
                } else {
                    Node* successor = node->right;
                    while (successor->left) successor = successor->left;
                    node->data = successor->data;
                    node->count = successor->count;
                    erase(node->right, successor->data);
                }
                delete oldNode;
                --size_;
            }
        }
    }

    void inorder(Node* node, std::function<void(const T&, size_t)> func) const {
        if (node) {
            inorder(node->left, func);
            func(node->data, node->count);
            inorder(node->right, func);
        }
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    Multiset() : root(nullptr), size_(0) {}

    ~Multiset() {
        clear(root);
    }

    void insert(const T& value) {
        insert(root, value);
        ++size_;
    }

    void erase(const T& value) {
        erase(root, value);
    }

    bool contains(const T& value) const {
        Node* node = root;
        while (node) {
            if (value < node->data) {
                node = node->left;
            } else if (value > node->data) {
                node = node->right;
            } else {
                return true;
            }
        }
        return false;
    }

    size_t count(const T& value) const {
        Node* node = root;
        while (node) {
            if (value < node->data) {
                node = node->left;
            } else if (value > node->data) {
                node = node->right;
            } else {
                return node->count;
            }
        }
        return 0;
    }

    size_t size() const {
        return size_;
    }

    void print() const {
        inorder(root, [](const T& value, size_t count) {
            std::cout << value << " (" << count << ") ";
        });
        std::cout << std::endl;
    }
};

template <typename K, typename V>
class Multimap {
private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        Node(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t size_;

    void insert(Node*& node, const K& key, const V& value) {
        if (!node) {
            node = new Node(key, value);
        } else if (key < node->key) {
            insert(node->left, key, value);
        } else if (key > node->key) {
            insert(node->right, key, value);
        } else {
            insert(node->right, key, value); // Handle duplicate keys
        }
    }

    void erase(Node*& node, const K& key) {
        if (!node) return;

        if (key < node->key) {
            erase(node->left, key);
        } else if (key > node->key) {
            erase(node->right, key);
        } else {
            // Node with the key found
            Node* oldNode = node;
            if (!node->left) {
                node = node->right;
            } else if (!node->right) {
                node = node->left;
            } else {
                Node* successor = node->right;
                while (successor->left) successor = successor->left;
                node->key = successor->key;
                node->value = successor->value;
                erase(node->right, successor->key);
            }
            delete oldNode;
            --size_;
        }
    }

    void inorder(Node* node, std::function<void(const K&, const V&)> func) const {
        if (node) {
            inorder(node->left, func);
            func(node->key, node->value);
            inorder(node->right, func);
        }
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    Multimap() : root(nullptr), size_(0) {}

    ~Multimap() {
        clear(root);
    }

    void insert(const K& key, const V& value) {
        insert(root, key, value);
        ++size_;
    }

    void erase(const K& key) {
        erase(root, key);
    }

    size_t size() const {
        return size_;
    }

    void print() const {
        inorder(root, [](const K& key, const V& value) {
            std::cout << "(" << key << ", " << value << ") ";
        });
        std::cout << std::endl;
    }
};
