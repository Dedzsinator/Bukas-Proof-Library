#pragma once

#include <iostream>

template <typename T, bool CIRCULAR = false>
class doublyLinkedList {
    private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int _size;

    public:
    doublyLinkedList() : head(nullptr), tail(nullptr), _size(0) {}


    ~doublyLinkedList() {
        clear();
    }


    void insert(T data) {
        Node* newNode = new Node(data);
        if (empty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        _size++;
    }


    void remove(T data) {
        if (empty()) return;
        Node* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                if (current == head) {
                    head = current->next;
                    if (head != nullptr) head->prev = nullptr;
                } else if (current == tail) {
                    tail = current->prev;
                    if (tail != nullptr) tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                _size--;
                return;
            }
            current = current->next;
        }
    }


    void print() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }


    bool search(T data) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == data) return true;
            current = current->next;
        }
        return false;
    }


    int size() {
        return _size;
    }


    bool empty() {
        return _size == 0;
    }


    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }


    T front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }


    T back() {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }


    std::ostream& operator<< (std::ostream& os) {
        Node* current = head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }


    std::istream& operator>> (std::istream& is) {
        T data;
        is >> data;
        insert(data);
        return is;
    }
};