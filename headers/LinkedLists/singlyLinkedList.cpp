#pragma once 
#include "../../headers/LinkedLists/singlyLinkedList.hpp"

template <typename T, bool CIRCULAR>
singlyLinkedList<T, CIRCULAR>::singlyLinkedList() : head(nullptr), _size(0) {}

template <typename T, bool CIRCULAR>
singlyLinkedList<T, CIRCULAR>::~singlyLinkedList() {
  clear();
}

template <typename T, bool CIRCULAR>
void singlyLinkedList<T, CIRCULAR>::insert(T data) {
  Node* newNode = new Node(data);
  if (head == nullptr) {
    head = newNode;
  } else {
    Node* temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
  _size++;
}

template <typename T, bool CIRCULAR>
void singlyLinkedList<T, CIRCULAR>::remove(T data) {
  if (head == nullptr) {
    return;
  }
  Node* temp = head;
  if (temp->data == data) {
    head = temp->next;
    delete temp;
    _size--;
    return;
  }
  while (temp->next != nullptr) {
    if (temp->next->data == data) {
      Node* toDelete = temp->next;
      temp->next = temp->next->next;
      delete toDelete;
      _size--;
      return;
    }
    temp = temp->next;
  }
}

template <typename T, bool CIRCULAR>
void singlyLinkedList<T, CIRCULAR>::print() {
  Node* temp = head;
  while (temp != nullptr) {
    std::cout << temp->data << " ";
    temp = temp->next;
  }
  std::cout << std::endl;
}

template <typename T, bool CIRCULAR>
bool singlyLinkedList<T, CIRCULAR>::search(T data) {
  Node* temp = head;
  while (temp != nullptr) {
    if (temp->data == data) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

template <typename T, bool CIRCULAR>
int singlyLinkedList<T, CIRCULAR>::size() {
  return _size;
}

template <typename T, bool CIRCULAR>
bool singlyLinkedList<T, CIRCULAR>::empty() {
  return _size == 0;
}

template <typename T, bool CIRCULAR>
void singlyLinkedList<T, CIRCULAR>::clear() {
  Node* temp = head;
  while (temp != nullptr) {
    Node* toDelete = temp;
    temp = temp->next;
    delete toDelete;
  }
  head = nullptr;
  _size = 0;
}

template <typename T, bool CIRCULAR>
T singlyLinkedList<T, CIRCULAR>::front() {
  if (head == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return head->data;
}

template <typename T, bool CIRCULAR>
std::ostream& singlyLinkedList<T, CIRCULAR>::operator<< (std::ostream& os) {
  Node* temp = head;
  while (temp != nullptr) {
    os << temp->data << " ";
    temp = temp->next;
  }
  return os;
}

template <typename T, bool CIRCULAR>
std::istream& singlyLinkedList<T, CIRCULAR>::operator>> (std::istream& is) {
  T data;
  is >> data;
  insert(data);
  return is;
}
