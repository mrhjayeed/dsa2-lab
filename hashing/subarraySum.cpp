#include <bits/stdc++.h>
using namespace std;

vector<int> subarraySum(vector<int>& arr, int target) {
    int n = arr.size();
    int start = 0;
    long long current_sum = 0;

    for (int end = 0; end < n; ++end) {
        current_sum += arr[end];

        while (current_sum > target && start < end) {
            current_sum -= arr[start];
            start++;
        }

        if (current_sum == target) {
            return {start + 1, end + 1};
        }
    }

    return {-1};
}

int main() {
    vector<int> arr = {15, 2, 4, 8, 9, 5, 10, 23};
    int target = 23;
    vector<int> result = subarraySum(arr, target);
    
    if (result.size() == 2) {
        cout << "Output: [" << result[0] << ", " << result[1] << "]\n";
    } else {
        cout << "Output: [" << result[0] << "]\n";
    }

    return 0;
}