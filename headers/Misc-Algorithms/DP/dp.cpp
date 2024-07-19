#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace dp {
    #define INT_MAX 1000000

    //Longest subsequence where it satisfies a function as condition
    int longestSubsequence(vector<int>& nums, int (*condition)(int, int)) {
        int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (condition(nums[i], nums[j])) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }

    //Fibonacci
    int fibonacci(int n) {
        if (n <= 1) {
            return n;
        }
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
    //0-1 Knapsack
    int knapsack(vector<int>& weights, vector<int>& values, int W) {
        int n = weights.size();
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int w = 1; w <= W; ++w) {
                if (weights[i - 1] <= w) {
                    dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[n][W];
    }

    //Longest Increasing Subsequence
    int longestIncreasingSubsequence(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }

    //Coin Change
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < coins.size(); ++j) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }

    //Minimum Path Sum
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }

    //matrix chain multiplication
    int matrixChainMultiplication(vector<int>& dims) {
        int n = dims.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int len = 2; len < n; ++len) {
            for (int i = 1; i < n - len + 1; ++i) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                for (int k = i; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j]);
                }
            }
        }
        return dp[1][n - 1];
    }

    //optimal binary search tree
    int optimalBinarySearchTree(vector<int>& keys, vector<int>& freq) {
        int n = keys.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = freq[i];
        }
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                int sum = 0;
                for (int k = i; k <= j; ++k) {
                    sum += freq[k];
                }
                for (int k = i; k <= j; ++k) {
                    int val = sum + (k - 1 >= i ? dp[i][k - 1] : 0) + (k + 1 <= j ? dp[k + 1][j] : 0);
                    dp[i][j] = min(dp[i][j], val);
                }
            }
        }
        return dp[0][n - 1];
    }

    //polygon triangulation
    int polygonTriangulation(vector<int>& vertices) {
        int n = vertices.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int len = 3; len < n; ++len) {
            for (int i = 0; i < n - len; ++i) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + vertices[i] * vertices[j] * vertices[k]);
                }
            }
        }
        return dp[0][n - 1];
    }

    //edit distance
    int editDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
            }
        }
        return dp[m][n];
    }
}