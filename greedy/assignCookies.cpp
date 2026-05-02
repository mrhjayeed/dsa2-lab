#include <bits/stdc++.h>
using namespace std;

int assign(vector<int>& greed, vector<int>& cookies) {
    sort(greed.begin(), greed.end());
    sort(cookies.begin(), cookies.end());

    int i = 0, j = 0;
    while(i < greed.size() &&  j < cookies.size()) {
        if (greed[i] <= cookies[j]) i++;
        j++;
    }

    return i;
}

int main() {
    vector<int> greed = {1, 10, 3};
    vector<int> cookies = {1, 2, 3};

    cout << assign(greed, cookies) << endl;

    return 0;
}