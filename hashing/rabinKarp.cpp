#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1e9 + 7;
const int BASE = 257;

vector<int> rabinKarp(const string& text, const string& pat) {
    int n = text.size(), m = pat.size();
    vector<int> result;
    if (m > n) return result;

    int highPow = 1;
    for (int i = 0; i < m - 1; i++) {
        highPow = highPow * BASE % MOD;
    }

    int patHash = 0, winHash = 0;
    for (int i = 0; i < m; i++) {
        patHash = (patHash * BASE + pat[i]) % MOD;
        winHash = (winHash * BASE + text[i]) % MOD;
    }

    for (int i = 0; i <= n - m; i++) {
        if (winHash == patHash) {
            if (text.substr(i, m) == pat) {
                result.push_back(i);
            }
        }

        if (i < n - m) {
            winHash = (winHash - text[i] * highPow % MOD + MOD) % MOD;
            winHash = (winHash * BASE + text[i + m]) % MOD;
        }
    }

    return result;
}

signed main() {
    string text = "abcabcabcabc";
    string pat = "abcabc";

    auto matches = rabinKarp(text, pat);
    
    if (matches.empty()) {
        cout << "Pattern not found\n";
    } else {
        cout << "Pattern found at indices: ";
        for (int idx : matches) cout << idx << " ";
        cout << "\n";
    }

    return 0;
}