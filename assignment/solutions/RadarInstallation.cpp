#include <bits/stdc++.h>
using namespace std;

struct Interval {
    double left, right;
};

bool compareByRight(const Interval &a, const Interval &b) {
    return a.right < b.right;
}

int radarInstallation(vector<pair<int, int>> &islands, int d) {
    int n = islands.size();

    vector<Interval> intervals(n);

    for (int i = 0; i < n; i++) {
        int x = islands[i].first;
        int y = islands[i].second;

        if (y > d) {
            return -1;
        }

        double offset = sqrt((double)d * d - (double)y * y);
        intervals[i].left = x - offset;
        intervals[i].right = x + offset;
    }

    sort(intervals.begin(), intervals.end(), compareByRight);

    int radarCount = 1;
    double currentRadar = intervals[0].right;  

    for (int i = 1; i < n; i++) {
        if (intervals[i].left > currentRadar) {
            radarCount++;
            currentRadar = intervals[i].right;
        }
    }

    return radarCount;
}

int main() {
    int n, d;
    cout << "Enter the number of islands: ";
    cin >> n;
    cout << "Enter the radar radius d: ";
    cin >> d;

    vector<pair<int, int>> islands(n);
    cout << "Enter the island coordinates (x y) one per line:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> islands[i].first >> islands[i].second;
    }

    int result = radarInstallation(islands, d);

    if (result == -1) {
        cout << "Output: -1" << endl;
        cout << "Explanation: It is impossible to cover all islands." << endl;
    } else {
        cout << "Minimum number of radars needed: " << result << endl;
    }

    return 0;
}