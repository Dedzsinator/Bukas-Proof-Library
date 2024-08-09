#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cmath>

using namespace std;

template <typename T, int minChildren>
class BTree {
private:
    struct Node {
        vector<T> data;
        vector<Node*> children;
        bool leaf;

        Node(bool leaf) : leaf(leaf) {}
    };

    Node* root;
    static const int t = minChildren;  // Minimum degree
    static const int maxChildren = 2 * t;
    static const int minKeys = t - 1;
    static const int maxKeys = 2 * t - 1;

    void splitChild(Node* parent, int index, Node* child) {
        Node* newChild = new Node(child->leaf);
        parent->children.insert(parent->children.begin() + index + 1, newChild);
        parent->data.insert(parent->data.begin() + index, child->data[t - 1]);

        newChild->data.assign(child->data.begin() + t, child->data.end());
        child->data.resize(t - 1);

        if (!child->leaf) {
            newChild->children.assign(child->children.begin() + t, child->children.end());
            child->children.resize(t);
        }
    }

    void insertNonFull(Node* node, const T& data) {
        int i = node->data.size() - 1;
        if (node->leaf) {
            node->data.push_back(data);
            while (i >= 0 && node->data[i] > data) {
                node->data[i + 1] = node->data[i];
                i--;
            }
            node->data[i + 1] = data;
        } else {
            while (i >= 0 && node->data[i] > data) {
                i--;
            }
            i++;
            if (node->children[i]->data.size() == maxKeys) {
                splitChild(node, i, node->children[i]);
                if (node->data[i] < data) {
                    i++;
                }
            }
            insertNonFull(node->children[i], data);
        }
    }

    void merge(Node* parent, int index) {
        Node* child1 = parent->children[index];
        Node* child2 = parent->children[index + 1];

        child1->data.push_back(parent->data[index]);
        child1->data.insert(child1->data.end(), child2->data.begin(), child2->data.end());
        child1->children.insert(child1->children.end(), child2->children.begin(), child2->children.end());

        parent->data.erase(parent->data.begin() + index);
        parent->children.erase(parent->children.begin() + index + 1);

        delete child2;
    }

    void removeFromNonLeaf(Node* node, int index) {
        T k = node->data[index];

        if (node->children[index]->data.size() >= t) {
            Node* cur = node->children[index];
            while (!cur->leaf) {
                cur = cur->children[cur->data.size()];
            }
            T pred = cur->data[cur->data.size() - 1];
            node->data[index] = pred;
            remove(node->children[index], pred);
        } else if (node->children[index + 1]->data.size() >= t) {
            Node* cur = node->children[index + 1];
            while (!cur->leaf) {
                cur = cur->children[0];
            }
            T succ = cur->data[0];
            node->data[index] = succ;
            remove(node->children[index + 1], succ);
        } else {
            merge(node, index);
            remove(node->children[index], k);
        }
    }

    void removeFromLeaf(Node* node, int index) {
        node->data.erase(node->data.begin() + index);
    }

    void remove(Node* node, const T& data) {
        int index = 0;
        while (index < node->data.size() && data > node->data[index]) {
            index++;
        }

        if (index < node->data.size() && node->data[index] == data) {
            if (node->leaf) {
                removeFromLeaf(node, index);
            } else {
                removeFromNonLeaf(node, index);
            }
        } else {
            if (node->leaf) {
                return;
            }

            bool flag = (index == node->data.size());

            if (node->children[index]->data.size() < t) {
                fill(node, index);
            }

            if (flag && index > node->data.size()) {
                remove(node->children[index - 1], data);
            } else {
                remove(node->children[index], data);
            }
        }
    }

    void fill(Node* node, int index) {
        if (index != 0 && node->children[index - 1]->data.size() >= t) {
            borrowFromPrev(node, index);
        } else if (index != node->data.size() && node->children[index + 1]->data.size() >= t) {
            borrowFromNext(node, index);
        } else {
            if (index != node->data.size()) {
                merge(node, index);
            } else {
                merge(node, index - 1);
            }
        }
    }

    void borrowFromPrev(Node* node, int index) {
        Node* child = node->children[index];
        Node* sibling = node->children[index - 1];

        child->data.insert(child->data.begin(), node->data[index - 1]);
        if (!child->leaf) {
            child->children.insert(child->children.begin(), sibling->children.back());
            sibling->children.pop_back();
        }

        node->data[index - 1] = sibling->data.back();
        sibling->data.pop_back();
    }

    void borrowFromNext(Node* node, int index) {
        Node* child = node->children[index];
        Node* sibling = node->children[index + 1];

        child->data.push_back(node->data[index]);
        if (!child->leaf) {
            child->children.push_back(sibling->children.front());
            sibling->children.erase(sibling->children.begin());
        }

        node->data[index] = sibling->data.front();
        sibling->data.erase(sibling->data.begin());
    }

public:
    BTree() {
        root = new Node(true);
    }

    BTree(const string& filename) {
        loadFromDisk(filename);
    }

    ~BTree() {
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            for (Node* child : node->children) {
                q.push(child);
            }
            delete node;
        }
    }

    void insert(const T& data) {
        if (root->data.size() == maxKeys) {
            Node* newRoot = new Node(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFull(root, data);
    }

    void remove(const T& data) {
        if (!root) {
            return;
        }

        remove(root, data);

        if (root->data.empty()) {
            Node* tmp = root;
            if (root->leaf) {
                root = nullptr;
            } else {
                root = root->children[0];
            }
            delete tmp;
        }
    }

    bool search(Node* node, const T& data) const {
        int i = 0;
        while (i < node->data.size() && data > node->data[i]) {
            i++;
        }

        if (i < node->data.size() && node->data[i] == data) {
            return true;
        }

        if (node->leaf) {
            return false;
        }

        return search(node->children[i], data);
    }

    void print(Node* node, int depth = 0) const {
        if (node) {
            for (int i = 0; i < node->data.size(); i++) {
                if (i < node->children.size()) {
                    print(node->children[i], depth + 1);
                }
                for (int j = 0; j < depth; j++) {
                    cout << "  ";
                }
                cout << node->data[i] << endl;
            }
            if (node->data.size() < node->children.size()) {
                print(node->children[node->data.size()], depth + 1);
            }
        }
    }

    void print() const {
        print(root);
    }

    void prettyPrint() const {
        if (!root) return;
    
        queue<Node*> currentLevel, nextLevel;
        currentLevel.push(root);
        int depth = 0;
    
        while (!currentLevel.empty()) {
            int levelSize = currentLevel.size();
            int spaces = pow(2, depth + 1) - 1;
            int betweenSpaces = pow(2, depth + 2) - 1;
    
            // Print leading spaces
            cout << setw(spaces) << "";
    
            for (int i = 0; i < levelSize; ++i) {
                Node* node = currentLevel.front();
                currentLevel.pop();
    
                // Print node data
                cout << "[ ";
                for (const auto& val : node->data) {
                    cout << val << " ";
                }
                cout << "]";
    
                // Print spaces between nodes
                if (i < levelSize - 1) {
                    cout << setw(betweenSpaces) << "";
                }
    
                // Enqueue children
                if (!node->leaf) {
                    for (auto* child : node->children) {
                        nextLevel.push(child);
                    }
                }
            }
            cout << endl;
    
            // Print edges
            if (!nextLevel.empty()) {
                cout << setw(spaces / 2) << "";
                for (int i = 0; i < levelSize; ++i) {
                    cout << "/\\";
                    if (i < levelSize - 1) {
                        cout << setw(betweenSpaces - 2) << "";
                    }
                }
                cout << endl;
            }
    
            swap(currentLevel, nextLevel);
            depth++;
        }
    }

    bool search(const T& data) const {
        return search(root, data);
    }

    void saveToDisk(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (file.is_open()) {
            saveNode(file, root);
            file.close();
        }
    }

    void loadFromDisk(const string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            root = loadNode(file);
            file.close();
        }
    }

private:
    void saveNode(ofstream& file, Node* node) const {
        if (node) {
            size_t dataSize = node->data.size();
            file.write(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
            file.write(reinterpret_cast<char*>(node->data.data()), dataSize * sizeof(T));

            size_t childrenSize = node->children.size();
            file.write(reinterpret_cast<char*>(&childrenSize), sizeof(childrenSize));
            for (Node* child : node->children) {
                saveNode(file, child);
            }
        } else {
            size_t dataSize = 0;
            file.write(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        }
    }

    Node* loadNode(ifstream& file) {
        size_t dataSize;
        file.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));

        if (dataSize == 0) {
            return nullptr;
        }

        Node* node = new Node(true);
        node->data.resize(dataSize);
        file.read(reinterpret_cast<char*>(node->data.data()), dataSize * sizeof(T));

        size_t childrenSize;
        file.read(reinterpret_cast<char*>(&childrenSize), sizeof(childrenSize));
        node->children.resize(childrenSize);
        for (size_t i = 0; i < childrenSize; i++) {
            node->children[i] = loadNode(file);
        }

        return node;
    }
};