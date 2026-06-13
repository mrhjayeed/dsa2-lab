#include <bits/stdc++.h>
using namespace std;

int findLongestConsecSubseq(vector<int>& arr) {
    unordered_set<int> elements(arr.begin(), arr.end());
    int longest_streak = 0;

    for (int num : elements) {
        if (elements.find(num - 1) == elements.end()) {
            int current_num = num;
            int current_streak = 1;

            while (elements.find(current_num + 1) != elements.end()) {
                current_num += 1;
                current_streak += 1;
            }

            longest_streak = max(longest_streak, current_streak);
        }
    }

    return longest_streak;
}

int main() {
    vector<int> arr = {2, 6, 1, 9, 4, 5, 3};
    cout << "Output: " << findLongestConsecSubseq(arr) << "\n";

    return 0;
}