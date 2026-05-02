#include <bits/stdc++.h>
using namespace std;

int cutRod(vector<int>& price, int n) {
    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        int max_val = INT_MIN;
        for (int j = 1; j <= i; j++) {
            max_val = max(max_val, price[j] + dp[i - j]);
        }
        dp[i] = max_val;
    }

    return dp[n];
}

int main() {
    vector<int> price = {0, 1, 5, 8, 9, 10, 17, 17, 20};
    int n = price.size() - 1;

    cout << cutRod(price, n) << endl;

    return 0;
}