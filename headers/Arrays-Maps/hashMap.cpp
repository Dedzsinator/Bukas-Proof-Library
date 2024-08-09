#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>

using namespace std;

template<typename KeyType, typename ValueType>
class HashTable {
private:
    class Bucket {
    public:
        KeyType key;
        ValueType value;
        bool is_occupied;

        Bucket() : is_occupied(false) {}
    };

    vector<Bucket> table;
    size_t current_size;
    static constexpr double load_factor_threshold = 0.75;

    size_t hash(const KeyType& key, size_t seed = 0) const {
        size_t len = key.size();
    
        // Check if the key has at least 2 characters
        if (len < 2) {
            // Hash it as an integer
            return static_cast<size_t>(key[0]) + seed;
        }
    
        // Use DJB2 hash function for smaller strings (length < 10)
        if (len < 10) {
            size_t hval = 5381 + seed;
            for (size_t i = 0; i < len; ++i) {
                hval = ((hval << 5) + hval) + static_cast<size_t>(key[i]); // hval * 33 + key[i]
            }
            return hval;
        }
    
        // Use a simpler hash function for longer strings
        size_t simple_hash = ((key[0] << 24) | (key[1] << 16) | (key[len - 2] << 8) | key[len - 1]) + seed;
        return simple_hash;
    }

    void resize(size_t new_capacity) {
        vector<Bucket> new_table(new_capacity);

        for (const auto& bucket : table) {
            if (bucket.is_occupied) {
                size_t index = hash(bucket.key) % new_capacity;
                while (new_table[index].is_occupied) {
                    index = (index + 1) % new_capacity;
                }
                new_table[index] = bucket;
            }
        }

        table = move(new_table);
    }

public:
    HashTable(size_t initial_capacity = 16) 
        : table(initial_capacity), current_size(0) {}

    void insert(const KeyType& key, const ValueType& value) {
        if (current_size >= table.size() * load_factor_threshold) {
            resize(table.size() * 2);
        }

        size_t seed = 0;
        size_t index = hash(key, seed) % table.size();

        while (table[index].is_occupied && table[index].key[0] == key[0]) {
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
            seed++;
            index = hash(key, seed) % table.size();
        }

        table[index].key = key;
        table[index].value = value;
        table[index].is_occupied = true;
        ++current_size;
    }

    bool remove(const KeyType& key) {
        size_t seed = 0;
        size_t index = hash(key, seed) % table.size();

        while (table[index].is_occupied && table[index].key[0] == key[0]) {
            if (table[index].key == key) {
                table[index].is_occupied = false;
                --current_size;
                return true;
            }
            seed++;
            index = hash(key, seed) % table.size();
        }
        return false;
    }

    bool search(const KeyType& key, ValueType& value) const {
        size_t seed = 0;
        size_t index = hash(key, seed) % table.size();

        while (table[index].is_occupied && table[index].key[0] == key[0]) {
            if (table[index].key == key) {
                value = table[index].value;
                return true;
            }
            seed++;
            index = hash(key, seed) % table.size();
        }
        return false;
    }

    ValueType& operator[](const KeyType& key) {
        size_t seed = 0;
        size_t index = hash(key, seed) % table.size();

        while (table[index].is_occupied && table[index].key[0] == key[0]) {
            if (table[index].key == key) {
                return table[index].value;
            }
            seed++;
            index = hash(key, seed) % table.size();
        }

        table[index].key = key;
        table[index].is_occupied = true;
        ++current_size;
        return table[index].value;
    }
};