#include <bits/stdc++.h>
using namespace std;

int rob(vector<int>& houses) {
    int n = houses.size();
    if (n == 0) return 0;
    if (n == 1) return houses[0];

    vector<int> dp(n + 1, 0);
    dp[1] = houses[0];

    for (int i = 2; i <= n; i++) {
        dp[i] = max(dp[i - 2] + houses[i - 1], dp[i - 1]);
    }

    return dp[n];
}

int main() {
    vector<int> houses = {50, 2, 5, 100, 50};

    cout << rob(houses) << endl;

    return 0;
}