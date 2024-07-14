#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INT_MIN -2147483648
#define INT_MAX 2147483647

namespace divide {
  //typical divide and conquer algorithms collection
  
  //Divide and conquer algorithm to find the maximum subarray
  //Time complexity: O(nlogn)
  //Space complexity: O(n)
  int maxSubArray(vector<int> arr, int low, int high) {
    if (low == high) {
      return arr[low];
    }
    int mid = (low + high) / 2;
    int leftMax = maxSubArray(arr, low, mid);
    int rightMax = maxSubArray(arr, mid + 1, high);
    int crossMax = 0;
    int leftSum = INT_MIN;
    int rightSum = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= low; i--) {
      sum += arr[i];
      if (sum > leftSum) {
        leftSum = sum;
      }
    }
    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
      sum += arr[i];
      if (sum > rightSum) {
        rightSum = sum;
      }
    }
    crossMax = leftSum + rightSum;
    return std::max(std::max(leftMax, rightMax), crossMax);
  }

  //recursive binary search
  //Time complexity: O(logn)
  //Space complexity: O(logn)
  //return the index of the target element in the input array
  int binarySearchRec(vector<int> arr, int low, int high, int target) {
    if (low > high) {
      return -1;
    }
    int mid = (low + high) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
      return binarySearchRec(arr, mid + 1, high, target);
    } else {
      return binarySearchRec(arr, low, mid - 1, target);
    }
  }

  //binary search
  //Time complexity: O(logn)
  //Space complexity: O(1)
  int binarySearch(vector<int> arr, int low, int high, int target) {
    if (low > high) {
      return -1;
    }
    int mid = (low + high) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
      return binarySearch(arr, mid + 1, high, target);
    } else {
      return binarySearch(arr, low, mid - 1, target);
    }
  }

  //2sum problem
  //Time complexity: O(nlogn)
  //Space complexity: O(1)
  //Assume the input array is sorted if not sort it first
  vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
      int index = divide::binarySearch(nums, i + 1, nums.size() - 1, target - nums[i]);
      if (index != -1) {
        result.push_back(i);
        result.push_back(index);
        break;
      }
    }
    return result;
  }

  //3sum problem
  //Time complexity: O(n^2)
  //Space complexity: O(1)
  //Assume the input array is sorted if not sort it first
  
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }
      int target = -nums[i];
      int left = i + 1;
      int right = nums.size() - 1;
      while (left < right) {
        if (nums[left] + nums[right] == target) {
          result.push_back({nums[i], nums[left], nums[right]});
          left++;
          right--;
          while (left < right && nums[left] == nums[left - 1]) {
            left++;
          }
          while (left < right && nums[right] == nums[right + 1]) {
            right--;
          }
        } else if (nums[left] + nums[right] < target) {
          left++;
        } else {
          right--;
        }
      }
    }
    return result;
  }

  //nsum problem
  //Time complexity: O(n^(k-1))
  //Space complexity: O(1)
  //Assume the input array is sorted if not sort it first
  //k is the number of elements that sum up to the target
  //n is the number of elements in the input array
  
  vector<vector<int>> nSum(vector<int>& nums, int target, int k) {
    vector<vector<int>> result;
    if (k == 2) {
      for (int i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
          continue;
        }
        int left = i + 1;
        int right = nums.size() - 1;
        while (left < right) {
          if (nums[left] + nums[right] == target - nums[i]) {
            result.push_back({nums[i], nums[left], nums[right]});
            left++;
            right--;
            while (left < right && nums[left] == nums[left - 1]) {
              left++;
            }
            while (left < right && nums[right] == nums[right + 1]) {
              right--;
            }
          } else if (nums[left] + nums[right] < target - nums[i]) {
            left++;
          } else {
            right--;
          }
        }
      }
    } else {
      for (int i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
          continue;
        }
        vector<vector<int>> temp = nSum(nums, target - nums[i], k - 1);
        for (int j = 0; j < temp.size(); j++) {
          temp[j].insert(temp[j].begin(), nums[i]);
          result.push_back(temp[j]);
        }
      }
    }
    return result;
  }

  //hanoi tower problem with k rods
  //Time complexity: O(2^n)
  //Space complexity: O(n)
  //n is the number of disks
  //k is the number of rods
  //return the minimum number of moves to move all disks to the last rod
  //return the sequence of moves
  pair<int, vector<pair<int, int>>> hanoiTower(int n, int k) {
    vector<pair<int, int>> moves;
    if (n == 0) {
      return {0, moves};
    }
    if (k == 1) {
      for (int i = 1; i <= n; i++) {
        moves.push_back({1, k});
      }
      return {n, moves};
    }
    pair<int, vector<pair<int, int>>> result = hanoiTower(n - 1, k - 1);
    int minMoves = result.first;
    moves = result.second;
    moves.push_back({1, k});
    result = hanoiTower(n - 1, k - 1);
    minMoves += result.first;
    moves.insert(moves.end(), result.second.begin(), result.second.end());
    return {minMoves, moves};
  }
  
  //russian peasant multiplication
  //Time complexity: O(logn)
  //Space complexity: O(1)
  //return the product of two numbers
  //a and b are the two numbers to be multiplied
  long long russianPeasantMultiplication(long long a, long long b) {
    long long result = 0;
    while (b > 0) {
      if (b % 2 == 1) {
        result += a;
      }
      a *= 2;
      b /= 2;
    }
    return result;
  }

  //quickselect
  //Time complexity: O(n)
  //Space complexity: O(1)
  //return the kth smallest element in the input array
  
  int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
      if (arr[j] < pivot) {
        i++;
        swap(arr[i], arr[j]);
      }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
  }

  int quickSelect(vector<int>& arr, int low, int high, int k) {
    if (low == high) {
      return arr[low];
    }
    int pivot = partition(arr, low, high);
    if (pivot == k) {
      return arr[pivot];
    } else if (pivot < k) {
      return quickSelect(arr, pivot + 1, high, k);
    } else {
      return quickSelect(arr, low, pivot - 1, k);
    }
  }

  //local minima
  //Time complexity: O(logn)
  //Space complexity: O(1)
  //return the index of the local minima in the input array
  int localMinima(vector<int>& arr, int low, int high) {
    if (low == high) {
      return low;
    }
    int mid = (low + high) / 2;
    if (arr[mid] < arr[mid - 1] && arr[mid] < arr[mid + 1]) {
      return mid;
    } else if (arr[mid - 1] < arr[mid + 1]) {
      return localMinima(arr, low, mid - 1);
    } else {
      return localMinima(arr, mid + 1, high);
    }
  }

  //find the two closest point in the 2 dimensional plane
  //Time complexity: O(nlogn)
  //Space complexity: O(1)
  //return the two closest points
  pair<int,int> closestPoints(vector<pair<int,int>>& points) {
    sort(points.begin(), points.end());
    int minDist = INT_MAX;
    pair<int,int> result;
    for (int i = 0; i < points.size() - 1; i++) {
      int dist = abs(points[i].first - points[i + 1].first) + abs(points[i].second - points[i + 1].second);
      if (dist < minDist) {
        minDist = dist;
        result = {i, i + 1};
      }
    }
    return result;
  }
}
