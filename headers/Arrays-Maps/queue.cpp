#pragma once

#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T value;
        Node* next;
    };
    Node* head;
    Node* tail;
    int count;

  public:
    Queue() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~Queue() {
        clear(*this);
    }

    void enqueue(T value) {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    T dequeue() {
        if (head == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        T value = head->value;
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return value;
    }

    T peek() {
        if (head == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        return head->value;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    int size() {
        return count;
    }

    Queue(const Queue<T>& other) {
        copy(*this, other);
    }

    Queue<T>& operator=(const Queue<T>& other) {
        if (this != &other) {
            clear(*this);
            copy(*this, other);
        }
        return *this;
    }

    Queue(Queue<T>&& other) {
        copy(*this, std::move(other));
    }

    Queue<T>& operator=(Queue<T>&& other) {
        if (this != &other) {
            clear(*this);
            copy(*this, std::move(other));
        }
        return *this;
    }

    bool operator==(const Queue<T>& other) {
        if (count != other.count) {
            return false;
        }
        Node* current = head;
        Node* otherCurrent = other.head;
        while (current != nullptr) {
            if (current->value != otherCurrent->value) {
                return false;
            }
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        return true;
    }

    bool operator!=(const Queue<T>& other) {
        return !(*this == other);
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Queue<U>& queue) {
        os << "Queue(";
        Node* current = queue.head;
        while (current != nullptr) {
            os << current->value;
            current = current->next;
            if (current != nullptr) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Queue<U>& queue);

    template <typename U>
    friend void swap(Queue<U>& first, Queue<U>& second) {
        std::swap(first.head, second.head);
        std::swap(first.tail, second.tail);
        std::swap(first.count, second.count);
    }

    template <typename U>
    friend void clear(Queue<U>& queue) {
        while (!queue.isEmpty()) {
            queue.dequeue();
        }
    
    }

    template <typename U>
    friend void copy(Queue<U>& dest, const Queue<U>& src) {
        Node* current = src.head;
        while (current != nullptr) {
            dest.enqueue(current->value);
            current = current->next;
        }
    }

    template <typename U>
    friend void copy(Queue<U>& dest, Queue<U>&& src) {
        dest.head = src.head;
        dest.tail = src.tail;
        dest.count = src.count;
        src.head = nullptr;
        src.tail = nullptr;
        src.count = 0;
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* current) : current(current) {}

        T operator*() {
            return current->value;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

template<class T>
class Queue<T*> {
private:
    struct Node {
        T* value;
        Node* next;
    };
    Node* head;
    Node* tail;
    int count;

public:
    Queue() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~Queue() {
        clear(*this);
    }

    void enqueue(T* value) {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    T* dequeue() {
        if (head == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        T* value = head->value;
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return value;
    }

    T* peek() {
        if (head == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        return head->value;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    int size() {
        return count;
    }

    Queue(const Queue<T*>& other) {
        copy(*this, other);
    }

    Queue<T*>& operator=(const Queue<T*>& other) {
        if (this != &other) {
            clear(*this);
            copy(*this, other);
        }
        return *this;
    }

    Queue(Queue<T*>&& other) {
        copy(*this, std::move(other));
    }

    Queue<T*>& operator=(Queue<T*>&& other) {
        if (this != &other) {
            clear(*this);
            copy(*this, std::move(other));
        }
        return *this;
    }

    bool operator==(const Queue<T*>& other) {
        if (count != other.count) {
            return false;
        }
        Node* current = head;
        Node* otherCurrent = other.head;
        while (current != nullptr) {
            if (*current->value != *otherCurrent->value) {
                return false;
            }
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        return true;
    }

    bool operator!=(const Queue<T*>& other) {
        return !(*this == other);
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Queue<U*>& queue) {
        os << "Queue(";
        Node* current = queue.head;
        while (current != nullptr) {
            os << *current->value;
            current = current->next;
            if (current != nullptr) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Queue<U*>& queue) {
        U* value = new U;
        is >> *value;
        queue.enqueue(value);
        return is;
    }

    template <typename U>
    friend void swap(Queue<U*>& first, Queue<U*>& second) {
        std::swap(first.head, second.head);
        std::swap(first.tail, second.tail);
        std::swap(first.count, second.count);
    }

    template <typename U>
    friend void clear(Queue<U*>& queue) {
        while (!queue.isEmpty()) {
            delete queue.dequeue();
        }
    }

    template <typename U>
    friend void copy(Queue<U*>& dest, const Queue<U*>& src) {
        Node* current = src.head;
        while (current != nullptr) {
            dest.enqueue(new U(*current->value));
            current = current->next;
        }
    }

    template <typename U>
    friend void copy(Queue<U*>& dest, Queue<U*>&& src) {
        dest.head = src.head;
        dest.tail = src.tail;
        dest.count = src.count;
        src.head = nullptr;
        src.tail = nullptr;
        src.count = 0;
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* current) : current(current) {}

        T* operator*() {
            return current->value;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

};