#pragma once
#include "../../headers/LinkedLists/doublyLinkedList.hpp"

template <typename T, bool CIRCULAR>
doublyLinkedList<T, CIRCULAR>::doublyLinkedList() : head(nullptr), tail(nullptr), _size(0) {}

template <typename T, bool CIRCULAR>
doublyLinkedList<T, CIRCULAR>::~doublyLinkedList() {
    clear();
}

template <typename T, bool CIRCULAR>
void doublyLinkedList<T, CIRCULAR>::insert(T data) {
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

template <typename T, bool CIRCULAR>
void doublyLinkedList<T, CIRCULAR>::remove(T data) {
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

template <typename T, bool CIRCULAR>
void doublyLinkedList<T, CIRCULAR>::print() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T, bool CIRCULAR>
bool doublyLinkedList<T, CIRCULAR>::search(T data) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data) return true;
        current = current->next;
    }
    return false;
}

template <typename T, bool CIRCULAR>
int doublyLinkedList<T, CIRCULAR>::size() {
    return _size;
}

template <typename T, bool CIRCULAR>
bool doublyLinkedList<T, CIRCULAR>::empty() {
    return _size == 0;
}

template <typename T, bool CIRCULAR>
void doublyLinkedList<T, CIRCULAR>::clear() {
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

template <typename T, bool CIRCULAR>
T doublyLinkedList<T, CIRCULAR>::front() {
    if (empty()) throw std::out_of_range("List is empty");
    return head->data;
}

template <typename T, bool CIRCULAR>
T doublyLinkedList<T, CIRCULAR>::back() {
    if (empty()) throw std::out_of_range("List is empty");
    return tail->data;
}

template <typename T, bool CIRCULAR>
std::ostream& doublyLinkedList<T, CIRCULAR>::operator<< (std::ostream& os) {
    Node* current = head;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
    return os;
}

template <typename T, bool CIRCULAR>
std::istream& doublyLinkedList<T, CIRCULAR>::operator>> (std::istream& is) {
    T data;
    is >> data;
    insert(data);
    return is;
}
