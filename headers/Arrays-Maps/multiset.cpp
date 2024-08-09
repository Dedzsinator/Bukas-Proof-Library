#include <iostream>
#include <stdexcept>

template<class T>
class MultiSet {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        size_t count;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), count(1) {}
    };

    Node* root;
    size_t size;

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* copy(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->count = node->count;
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    Node* insert(Node* node, const T& value) {
        if (!node) {
            ++size;
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            ++node->count;
        }
        return node;
    }

    Node* erase(Node* node, const T& value) {
        if (!node) return nullptr;
        if (value < node->data) {
            node->left = erase(node->left, value);
        } else if (value > node->data) {
            node->right = erase(node->right, value);
        } else {
            if (node->count > 1) {
                --node->count;
            } else {
                if (!node->left) {
                    Node* rightChild = node->right;
                    delete node;
                    --size;
                    return rightChild;
                } else if (!node->right) {
                    Node* leftChild = node->left;
                    delete node;
                    --size;
                    return leftChild;
                } else {
                    Node* minNode = findMin(node->right);
                    node->data = minNode->data;
                    node->count = minNode->count;
                    minNode->count = 1;
                    node->right = erase(node->right, minNode->data);
                }
            }
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    size_t count(Node* node, const T& value) const {
        if (!node) return 0;
        if (value < node->data) {
            return count(node->left, value);
        } else if (value > node->data) {
            return count(node->right, value);
        } else {
            return node->count;
        }
    }

public:
    MultiSet() : root(nullptr), size(0) {}

    MultiSet(const MultiSet<T>& other) : root(nullptr), size(0) {
        root = copy(other.root);
        size = other.size;
    }

    MultiSet<T>& operator=(const MultiSet<T>& other) {
        if (this != &other) {
            clear(root);
            root = copy(other.root);
            size = other.size;
        }
        return *this;
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    void erase(const T& value) {
        root = erase(root, value);
    }

    size_t count(const T& value) const {
        return count(root, value);
    }

    size_t get_size() const {
        return size;
    }

    ~MultiSet() {
        clear(root);
    }
};

template<class T>
class MultiMap {
    private:
        struct Node {
            T key;
            T value;
            Node* left;
            Node* right;
            size_t count;

            Node(const T& key, const T& value) : key(key), value(value), left(nullptr), right(nullptr), count(1) {}
        };

        Node* root;
        size_t size;

        void clear(Node* node) {
            if (node) {
                clear(node->left);
                clear(node->right);
                delete node;
            }
        }

        Node* copy(Node* node) {
            if (!node) return nullptr;
            Node* newNode = new Node(node->key, node->value);
            newNode->count = node->count;
            newNode->left = copy(node->left);
            newNode->right = copy(node->right);
            return newNode;
        }

        Node* insert(Node* node, const T& key, const T& value) {
            if (!node) {
                ++size;
                return new Node(key, value);
            }
            if (key < node->key) {
                node->left = insert(node->left, key, value);
            } else if (key > node->key) {
                node->right = insert(node->right, key, value);
            } else {
                ++node->count;
            }
            return node;
        }

        Node* erase(Node* node, const T& key) {
            if (!node) return nullptr;
            if (key < node->key) {
                node->left = erase(node->left, key);
            } else if (key > node->key) {
                node->right = erase(node->right, key);
            } else {
                if (node->count > 1) {
                    --node->count;
                } else {
                    if (!node->left) {
                        Node* rightChild = node->right;
                        delete node;
                        --size;
                        return rightChild;
                    } else if (!node->right) {
                        Node* leftChild = node->left;
                        delete node;
                        --size;
                        return leftChild;
                    } else {
                        Node* minNode = findMin(node->right);
                        node->key = minNode->key;
                        node->value = minNode->value;
                        node->count = minNode->count;
                        minNode->count = 1;
                        node->right = erase(node->right, minNode->key);
                    }
                }
            }
            return node;
        }

        Node* findMin(Node* node) {
            while (node->left) {
                node = node->left;
            }
            return node;
        }

        size_t count(Node* node, const T& key) const {
            if (!node) return 0;
            if (key < node->key) {
                return count(node->left, key);
            } else if (key > node->key) {
                return count(node->right, key);
            } else {
                return node->count;
            }
        }

    public:
        MultiMap() : root(nullptr), size(0) {}

        MultiMap(const MultiMap<T>& other) : root(nullptr), size(0) {
            root = copy(other.root);
            size = other.size;
        }

        MultiMap<T>& operator=(const MultiMap<T>& other) {
            if (this != &other) {
                clear(root);
                root = copy(other.root);
                size = other.size;
            }
            return *this;
        }

        void insert(const T& key, const T& value) {
            root = insert(root, key, value);
        }

        void erase(const T& key) {
            root = erase(root, key);
        }

        size_t count(const T& key) const {
            return count(root, key);
        }

        size_t get_size() const {
            return size;
        }

        ~MultiMap() {
            clear(root);
        }
};