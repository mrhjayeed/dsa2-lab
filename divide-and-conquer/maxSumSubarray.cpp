#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// Function to find the maximum sum crossing the middle element
int maxCrossingSum(const vector<int>& arr, int low, int mid, int high) {
    // 1. Find the maximum sum extending to the left of the midpoint
    int left_sum = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
        }
    }

    // 2. Find the maximum sum extending to the right of the midpoint
    int right_sum = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += arr[i];
        if (sum > right_sum) {
            right_sum = sum;
        }
    }

    // 3. Return the combined sum 
    return left_sum + right_sum;
}

// Function to find the maximum contiguous subarray sum
int maxSubArraySum(const vector<int>& arr, int low, int high) {
    // Base Case: Only one element in the array
    if (low == high) {
        return arr[low];
    }

    // Find the midpoint
    int mid = low + (high - low) / 2;

    // Recursively find the max subarray sum for the left and right halves
    int left_half_sum = maxSubArraySum(arr, low, mid);
    int right_half_sum = maxSubArraySum(arr, mid + 1, high);
    
    // Find the max subarray sum that crosses the midpoint
    int crossing_sum = maxCrossingSum(arr, low, mid, high);

    // Return the maximum of the three possibilities
    return max({left_half_sum, right_half_sum, crossing_sum});
}

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = arr.size();

    int max_sum = maxSubArraySum(arr, 0, n - 1);

    cout << "The maximum contiguous subarray sum is: " << max_sum << endl;

    return 0;
}