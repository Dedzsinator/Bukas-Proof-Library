#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <cassert>

// Define some macros for common alphabet sizes
#define ASCII_SIZE 128
#define ALPHANUMERIC_SIZE 36
#define LOWERCASE_SIZE 26
#define UPPERCASE_SIZE 26
#define UTF8_SIZE 256
#define UNICODE_SIZE 65536
#define EXTENDED_ASCII_SIZE 256

// Helper function to hash keys into the alphabet range
template<typename KeyType>
struct KeyHasher {
    size_t operator()(const KeyType& key) const {
        std::hash<KeyType> hasher;
        return hasher(key);  // Default hash function (O(1) for most cases)
    }
};

// Trie Node structure
template<typename KeyType, typename ValueType, size_t ALPHABET_SIZE = ASCII_SIZE, typename Hasher = KeyHasher<KeyType>>
class TrieNode {
public:
    // Each node holds an array of children (fixed size for cache locality)
    std::array<std::unique_ptr<TrieNode>, ALPHABET_SIZE> children{};
    bool isEndOfWord;
    ValueType value;  // Store any value associated with the key

    TrieNode() : isEndOfWord(false), value(ValueType{}) {}
};

// Trie data structure
template<typename KeyType, typename ValueType, size_t ALPHABET_SIZE = ASCII_SIZE, typename Hasher = KeyHasher<KeyType>>
class Trie {
private:
    std::unique_ptr<TrieNode<KeyType, ValueType, ALPHABET_SIZE, Hasher>> root;
    Hasher hasher;  // Hasher function to convert keys to indices

    // Helper function to get the index of a key for a given character in the alphabet range
    size_t getIndex(const KeyType& keyPart) const {
        size_t hashValue = hasher(keyPart);
        return hashValue % ALPHABET_SIZE;  // Modulo to restrict to alphabet range
    }

    // Helper function to collect all keys in the Trie
    void collectKeys(TrieNode<KeyType, ValueType, ALPHABET_SIZE, Hasher>* node, std::vector<KeyType>& currentKey, std::vector<std::vector<KeyType>>& keys) const {
        if (node->isEndOfWord) {
            keys.push_back(currentKey);
        }

        for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                currentKey.push_back(static_cast<KeyType>(i));
                collectKeys(node->children[i].get(), currentKey, keys);
                currentKey.pop_back();
            }
        }
    }

public:
    Trie() {
        root = std::make_unique<TrieNode<KeyType, ValueType, ALPHABET_SIZE, Hasher>>();
    }

    // Function to insert a key-value pair into the trie
    void insert(const std::vector<KeyType>& key, const ValueType& value) {
        TrieNode<KeyType, ValueType, ALPHABET_SIZE, Hasher>* node = root.get();

        for (const KeyType& keyPart : key) {
            size_t index = getIndex(keyPart);
            if (!node->children[index]) {
                node->children[index] = std::make_unique<TrieNode<KeyType, ValueType, ALPHABET_SIZE, Hasher>>();
            }
            node = node->children[index].get();
        }

        // Mark the last node as the end of the key and store the value
        node->isEndOfWord = true;
        node->value = value;
    }

    // Function to search for a key in the trie
    bool search(const std::vector<KeyType>& key, ValueType& result) const {
        TrieNode<KeyType, ValueType, ALPHABET_SIZE, Hasher>* node = root.get();

        for (const KeyType& keyPart : key) {
            size_t index = getIndex(keyPart);
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index].get();
        }

        // Check if we reached the end of a word
        if (node && node->isEndOfWord) {
            result = node->value;
            return true;
        }

        return false;
    }

    // Function to check if a prefix exists in the trie
    bool startsWith(const std::vector<KeyType>& prefix) const {
        TrieNode<KeyType, ValueType, ALPHABET_SIZE, Hasher>* node = root.get();

        for (const KeyType& keyPart : prefix) {
            size_t index = getIndex(keyPart);
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index].get();
        }

        return true;
    }

    // Function to get all keys in sorted order
    std::vector<std::vector<KeyType>> getSortedKeys() const {
        std::vector<std::vector<KeyType>> keys;
        std::vector<KeyType> currentKey;
        collectKeys(root.get(), currentKey, keys);
        return keys;
    }
};

void test_insert_key_value() {
    Trie<char, int> trie;
    std::vector<char> key = {'a', 'b', 'c'};
    trie.insert(key, 123);

    int result;
    bool found = trie.search(key, result);
    assert(found == true);
    assert(result == 123);
}

void test_search_existing_key() {
    Trie<char, int> trie;
    std::vector<char> key = {'x', 'y', 'z'};
    trie.insert(key, 456);

    int result;
    bool found = trie.search(key, result);
    assert(found == true);
    assert(result == 456);
}

void test_sorting() {
    Trie<char, int> trie;
    std::vector<char> key1 = {'a', 'b', 'c'};
    std::vector<char> key2 = {'x', 'y', 'z'};
    trie.insert(key1, 123);
    trie.insert(key2, 456);

    std::vector<std::vector<char>> keys = trie.getSortedKeys();
    assert(keys.size() == 2);
    assert(keys[0] == key1);
    assert(keys[1] == key2);
}

void test_starts_with_existing_prefix() {
    Trie<char, int> trie;
    std::vector<char> key = {'p', 'r', 'e', 'f', 'i', 'x'};
    trie.insert(key, 789);

    std::vector<char> prefix = {'p', 'r', 'e'};
    bool startsWith = trie.startsWith(prefix);
    assert(startsWith == true);
}

int main() {
    test_insert_key_value();
    test_search_existing_key();
    test_starts_with_existing_prefix();
    test_sorting();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
