#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace greedy {

    // Activity Selection
    int activitySelection(vector<int>& start, vector<int>& finish) {
        int n = start.size();
        vector<pair<int, int>> activities;
        for (int i = 0; i < n; ++i) {
            activities.push_back({finish[i], start[i]});
        }
        sort(activities.begin(), activities.end());
        int count = 1;
        int last_finish = activities[0].first;
        for (int i = 1; i < n; ++i) {
            if (activities[i].second >= last_finish) {
                count++;
                last_finish = activities[i].first;
            }
        }
        return count;
    }

    // Fractional Knapsack
    double fractionalKnapsack(vector<int>& weights, vector<int>& values, int W) {
        int n = weights.size();
        vector<pair<double, int>> value_per_weight(n);
        for (int i = 0; i < n; ++i) {
            value_per_weight[i] = {values[i] / (double)weights[i], i};
        }
        sort(value_per_weight.begin(), value_per_weight.end(), greater<pair<double, int>>());
        double total_value = 0;
        for (int i = 0; i < n; ++i) {
            int index = value_per_weight[i].second;
            if (weights[index] <= W) {
                total_value += values[index];
                W -= weights[index];
            } else {
                total_value += value_per_weight[i].first * W;
                break;
            }
        }
        return total_value;
    }

    // Coin Change
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        sort(coins.begin(), coins.end(), greater<int>());
        int count = 0;
        for (int i = 0; i < n; ++i) {
            count += amount / coins[i];
            amount %= coins[i];
        }
        return count;
    }

}