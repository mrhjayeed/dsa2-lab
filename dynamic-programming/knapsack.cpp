#include <bits/stdc++.h>
using namespace std;

int knapsack(int cap, vector<int>& weights, vector<int>& values) {
    int n = weights.size();

    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= cap; j++) {
            if (weights[i - 1] <= j) {
                dp[i][j] = max(
                    values[i - 1] + dp[i - 1][j - weights[i - 1]],
                    dp[i - 1][j]
                );
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][cap];
}

int main() {
    vector<int> weights = {2, 1, 3, 2};
    vector<int> values = {12, 10, 20, 15};

    int cap = 5;

    cout << knapsack(cap, weights, values) << endl;

    return 0;
}