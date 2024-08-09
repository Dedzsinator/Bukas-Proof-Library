#include <iostream>
#include <cstdlib>
#include <ctime>

template<class T>
class SkipList {
private:
    struct Node {
        T data;
        Node* next;
        Node* down;
        Node(const T& data, Node* next = nullptr, Node* down = nullptr)
            : data(data), next(next), down(down) {}
    };

    Node* head;
    size_t size;
    size_t levels;

    Node* create_node(const T& data, Node* next = nullptr, Node* down = nullptr) {
        return new Node(data, next, down);
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* down = current->down;
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            current = down;
        }
    }

    void copy_from(const SkipList<T>& other) {
        if (this == &other) return;
        clear();
        size = other.size;
        levels = other.levels;
        if (!other.head) {
            head = nullptr;
            return;
        }

        head = create_node(other.head->data);
        Node* current = head;
        Node* other_current = other.head->next;
        while (other_current) {
            current->next = create_node(other_current->data);
            current = current->next;
            other_current = other_current->next;
        }

        Node* down = head;
        Node* other_down = other.head->down;
        while (other_down) {
            Node* new_level = create_node(other_down->data);
            down->down = new_level;
            current = new_level;
            other_current = other_down->next;
            while (other_current) {
                current->next = create_node(other_current->data);
                current = current->next;
                other_current = other_current->next;
            }
            down = down->down;
            other_down = other_down->down;
        }
    }

public:
    SkipList() : head(nullptr), size(0), levels(1) {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    SkipList(size_t levels) : head(nullptr), size(0), levels(levels) {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    SkipList(size_t levels, const T& val) : SkipList(levels) {
        for (size_t i = 0; i < levels; ++i) {
            insert(val);
        }
    }

    SkipList(const SkipList<T>& other) : head(nullptr), size(0), levels(1) {
        copy_from(other);
    }

    SkipList<T>& operator=(const SkipList<T>& other) {
        if (this != &other) {
            copy_from(other);
        }
        return *this;
    }

    void insert(const T& value) {
        Node* current = head;
        Node* last = nullptr;
        Node* down = nullptr;
        size_t level = 0;

        while (current) {
            if (current->next && current->next->data < value) {
                current = current->next;
            } else {
                if (level == 0 || rand() % 2 == 0) {
                    Node* new_node = create_node(value, current->next, down);
                    current->next = new_node;
                    down = new_node;
                    if (level == 0) {
                        ++size;
                    }
                }
                current = current->down;
                ++level;
            }
        }

        if (level > levels) {
            head = create_node(value, nullptr, head);
            ++levels;
        }
    }

    void remove(const T& value) {
        Node* current = head;
        bool found = false;

        while (current) {
            if (current->next && current->next->data < value) {
                current = current->next;
            } else {
                if (current->next && current->next->data == value) {
                    Node* to_delete = current->next;
                    current->next = to_delete->next;
                    delete to_delete;
                    found = true;
                }
                current = current->down;
            }
        }

        if (found) {
            --size;
        }
    }

    bool find(const T& value) {
        Node* current = head;

        while (current) {
            if (current->next && current->next->data < value) {
                current = current->next;
            } else {
                if (current->next && current->next->data == value) {
                    return true;
                }
                current = current->down;
            }
        }

        return false;
    }

    size_t get_size() {
        return size;
    }

    ~SkipList() {
        clear();
    }
};