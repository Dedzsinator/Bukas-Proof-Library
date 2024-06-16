#pragma once 

#include <iostream>

template <typename K, typename V>

class HashTable {
    struct Node {
        int data;
        int count;
        Node* next;
    };

    Node** table;
    int size;
    int maxSize;

public:
    HashTable(int maxSize);
    ~HashTable();
    void insert(int data);
    void remove(int data);
    int search(int data);
    size_t calc_hash(int data);
    bool resize();

    HashTable(const HashTable<K, V>& other);

    HashTable<K, V>& operator=(const HashTable<K, V>& other);

    HashTable(HashTable<K, V>&& other);

    HashTable<K, V>& operator=(HashTable<K, V>&& other);

    bool operator==(const HashTable<K, V>& other);

    bool operator!=(const HashTable<K, V>& other);

    template <typename U, typename W>
    friend std::ostream& operator<<(std::ostream& os, const HashTable<U, W>& hashTable);

    template <typename U, typename W>
    friend std::istream& operator>>(std::istream& is, HashTable<U, W>& hashTable);

    template <typename U, typename W>
    friend void swap(HashTable<U, W>& first, HashTable<U, W>& second);

    template <typename U, typename W>
    friend void clear(HashTable<U, W>& hashTable);

    template <typename U, typename W>
    friend void copy(HashTable<U, W>& dest, const HashTable<U, W>& src);
};

template <typename K, typename V>
class OHashTable {

  private:
    struct Node {
        K key;
        V value;
        bool deleted;
        Node(K key, V value) : key(key), value(value), deleted(false) {}
    };

    Node** table;
    int size;
    int maxSize;

    int hash1(K key) {
        return key % maxSize;
    }

    int hash2(K key) {
        return 1 + (key % (maxSize - 1));
    }

    int find(K key) {
        int index = hash1(key);
        int i = 0;
        while (table[index] != nullptr && table[index]->key != key && i < maxSize) {
            index = (hash1(key) + i * hash2(key)) % maxSize;
            i++;
        }
        return index;
    }

    void resize() {
        int oldSize = maxSize;
        maxSize *= 2;
        Node** oldTable = table;
        table = new Node*[maxSize];
        for (int i = 0; i < maxSize; i++) {
            table[i] = nullptr;
        }
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != nullptr && !oldTable[i]->deleted) {
                int index = find(oldTable[i]->key);
                table[index] = oldTable[i];
            }
        }
        delete[] oldTable;
    }

  public:
    OHashTable(int maxSize) : size(0), maxSize(maxSize) {
        table = new Node*[maxSize];
        for (int i = 0; i < maxSize; i++) {
            table[i] = nullptr;
        }
    }

    ~OHashTable() {
        for (int i = 0; i < maxSize; i++) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
        delete[] table;
    }

    void insert(K key, V value) {
        if (size >= maxSize / 2) {
            resize();
        }
        int index = find(key);
        if (table[index] == nullptr) {
            table[index] = new Node(key, value);
            size++;
        } else {
            table[index]->value = value;
        }
    }

    void remove(K key) {
        int index = find(key);
        if (table[index] != nullptr) {
            table[index]->deleted = true;
            size--;
        }
    }

    V search(K key) {
        int index = find(key);
        if (table[index] != nullptr) {
            return table[index]->value;
        }
        return V();
    }

    void print() {
        for (int i = 0; i < maxSize; i++) {
            if (table[i] != nullptr) {
                std::cout << table[i]->key << " " << table[i]->value << std::endl;
            }
        }
    }
};
