#include <bits/stdc++.h>
using namespace std;

struct Activity {
    int start, finish;
};

bool cmp(Activity a, Activity b) {
    return a.finish < b.finish;
}

int activitySelection(vector<Activity>& acts) {
    sort(acts.begin(), acts.end(), cmp);

    int n = acts.size();

    int i = 0;
    int totalActivity = 1;
    for (int j = 1; j < n; j++) {
        if (acts[i].finish <= acts[j].start) {
            totalActivity++;
            i = j;
        }
    }

    return totalActivity;
}

int main() {
    vector<Activity> acts = {
        {1, 2},
        {3, 4},
        {0, 6},
        {5, 7},
        {8, 9},
        {5, 9}
    };

    cout << activitySelection(acts) << endl;

    return 0;
}