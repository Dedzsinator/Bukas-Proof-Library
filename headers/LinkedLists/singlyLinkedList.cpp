#pragma once

#include <iostream>

template <typename T, bool CIRCULAR = false>
class singlyLinkedList {
  private:
    struct Node {
      T data;
      Node* next;
      Node(T data) : data(data), next(nullptr) {}
    };

    Node* head;
    int _size;

  public:
    singlyLinkedList() : head(nullptr), _size(0) {}
    
    ~singlyLinkedList() {
      clear();
    }


    void insert(T data) {
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


    void remove(T data) {
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


    void print() {
      Node* temp = head;
      while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
      }
      std::cout << std::endl;
    }


    bool search(T data) {
      Node* temp = head;
      while (temp != nullptr) {
        if (temp->data == data) {
          return true;
        }
        temp = temp->next;
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
      Node* temp = head;
      while (temp != nullptr) {
        Node* toDelete = temp;
        temp = temp->next;
        delete toDelete;
      }
      head = nullptr;
      _size = 0;
    }


    T front() {
      if (head == nullptr) {
        throw std::out_of_range("List is empty");
      }
      return head->data;
    }


    std::ostream& operator<< (std::ostream& os) {
      Node* temp = head;
      while (temp != nullptr) {
        os << temp->data << " ";
        temp = temp->next;
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