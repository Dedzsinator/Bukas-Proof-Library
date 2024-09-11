#include <vector>
#include <iostream>

using namespace std;

class TrieNode {
public:
    TrieNode* children[2];
    int count;

    TrieNode() {
        children[0] = children[1] = nullptr;
        count = 0;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(int num) {
        TrieNode* node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) {
                node->children[bit] = new TrieNode();
            }
            node = node->children[bit];
            node->count++;
        }
    }

    int countLessThan(int num, int limit) {
        TrieNode* node = root;
        int count = 0;
        for (int i = 31; i >= 0; i--) {
            if (!node) break;
            int bitNum = (num >> i) & 1;
            int bitLimit = (limit >> i) & 1;
            if (bitLimit == 1) {
                if (node->children[bitNum]) {
                    count += node->children[bitNum]->count;
                }
                node = node->children[1 - bitNum];
            } else {
                node = node->children[bitNum];
            }
        }
        return count;
    }
};

class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        Trie trie;
        int count = 0;
        for (int num : nums) {
            count += trie.countLessThan(num, high + 1) - trie.countLessThan(num, low);
            trie.insert(num);
        }
        return count;
    }
};

// Example usage
int main() {
    Solution sol;
    vector<int> nums = {1, 4, 2, 7};
    int low = 2, high = 6;
    cout << sol.countPairs(nums, low, high) << endl; // Expected output: 6
    return 0;
}