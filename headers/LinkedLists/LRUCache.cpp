#include <iostream>
#include <unordered_map>

template<class T>
class LRUCache {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;
    size_t capacity;
    std::unordered_map<T, Node*> cache_map;

    void move_to_head(Node* node) {
        if (node == head) return;
        if (node == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        node->next = head;
        node->prev = nullptr;
        head->prev = node;
        head = node;
    }

    void remove_tail() {
        if (tail) {
            cache_map.erase(tail->data);
            if (tail->prev) {
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
            } else {
                delete tail;
                head = tail = nullptr;
            }
            --size;
        }
    }

public:
    LRUCache() : head(nullptr), tail(nullptr), size(0), capacity(0) {}

    LRUCache(size_t capacity) : head(nullptr), tail(nullptr), size(0), capacity(capacity) {}

    LRUCache(size_t capacity, const T& val) : LRUCache(capacity) {
        for (size_t i = 0; i < capacity; ++i) {
            insert(val);
        }
    }

    LRUCache(const LRUCache<T>& other) : LRUCache(other.capacity) {
        Node* current = other.head;
        while (current) {
            insert(current->data);
            current = current->next;
        }
    }

    LRUCache<T>& operator=(const LRUCache<T>& other) {
        if (this == &other) return *this;
        while (head) {
            remove_tail();
        }
        capacity = other.capacity;
        Node* current = other.head;
        while (current) {
            insert(current->data);
            current = current->next;
        }
        return *this;
    }

    void insert(const T& value) {
        if (cache_map.find(value) != cache_map.end()) {
            move_to_head(cache_map[value]);
        } else {
            Node* new_node = new Node(value);
            if (size == capacity) {
                remove_tail();
            }
            if (!head) {
                head = tail = new_node;
            } else {
                new_node->next = head;
                head->prev = new_node;
                head = new_node;
            }
            cache_map[value] = new_node;
            ++size;
        }
    }

    void remove(const T& value) {
        if (cache_map.find(value) != cache_map.end()) {
            Node* node = cache_map[value];
            if (node == head) {
                head = head->next;
                if (head) head->prev = nullptr;
            } else if (node == tail) {
                tail = tail->prev;
                if (tail) tail->next = nullptr;
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            delete node;
            cache_map.erase(value);
            --size;
        }
    }

    bool find(const T& value) {
        if (cache_map.find(value) != cache_map.end()) {
            move_to_head(cache_map[value]);
            return true;
        }
        return false;
    }

    size_t get_size() {
        return size;
    }

    ~LRUCache() {
        while (head) {
            remove_tail();
        }
    }
};