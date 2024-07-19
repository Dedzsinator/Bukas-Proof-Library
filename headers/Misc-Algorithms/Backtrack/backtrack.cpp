#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

namespace backtrack {

        void generatePermutationsHelper(std::vector<int>& nums, int start, std::function<void(const std::vector<int>&)> callback) {
        if (start == nums.size()) {
            callback(nums);
            return;
        }
        for (int i = start; i < nums.size(); ++i) {
            swap(nums, start, i);
            generatePermutationsHelper(nums, start + 1, callback);
            swap(nums, start, i);
        }
    }

    void generatePermutations(const std::vector<int>& nums, std::function<void(const std::vector<int>&)> callback) {
        std::vector<int> nums_copy = nums;
        generatePermutationsHelper(nums_copy, 0, callback);
    }

    // Combinations
    void generateCombinationsHelper(int n, int k, int start, std::vector<int>& current, std::function<void(const std::vector<int>&)> callback) {
        if (current.size() == k) {
            callback(current);
            return;
        }
        for (int i = start; i <= n; ++i) {
            current.push_back(i);
            generateCombinationsHelper(n, k, i + 1, current, callback);
            current.pop_back();
        }
    }

    void generateCombinations(int n, int k, std::function<void(const std::vector<int>&)> callback) {
        std::vector<int> current;
        generateCombinationsHelper(n, k, 1, current, callback);
    }

    // Subsets
    void generateSubsetsHelper(const std::vector<int>& nums, int start, std::vector<int>& current, std::function<void(const std::vector<int>&)> callback) {
        callback(current);
        for (int i = start; i < nums.size(); ++i) {
            current.push_back(nums[i]);
            generateSubsetsHelper(nums, i + 1, current, callback);
            current.pop_back();
        }
    }

    void generateSubsets(const std::vector<int>& nums, std::function<void(const std::vector<int>&)> callback) {
        std::vector<int> current;
        generateSubsetsHelper(nums, 0, current, callback);
    }

    // N-Queens
    bool isSafe(const std::vector<std::string>& board, int row, int col, int n) {
        for (int i = 0; i < col; ++i)
            if (board[row][i] == 'Q') return false;
        for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
            if (board[i][j] == 'Q') return false;
        for (int i = row, j = col; i < n && j >= 0; ++i, --j)
            if (board[i][j] == 'Q') return false;
        return true;
    }

    void solveNQueensHelper(int col, int n, std::vector<std::string>& board, std::function<void(const std::vector<std::vector<std::string>>&) > callback) {
        if (col >= n) {
            callback({board});
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (isSafe(board, i, col, n)) {
                board[i][col] = 'Q';
                solveNQueensHelper(col + 1, n, board, callback);
                board[i][col] = '.';
            }
        }
    }

    void solveNQueens(int n, std::function<void(const std::vector<std::vector<std::string>>&) > callback) {
        std::vector<std::string> board(n, std::string(n, '.'));
        solveNQueensHelper(0, n, board, callback);
    }
}