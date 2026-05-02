#include <bits/stdc++.h>
using namespace std;

struct Item {
    int value, weight;
};

bool cmp(Item a, Item b) {
    double r1 = ((double)a.value / a.weight);
    double r2 = ((double)b.value / b.weight);
    return r1 > r2;
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(), cmp);

    double totalValue = 0.0;

    for (auto& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            totalValue += (capacity * ((double)item.value / item.weight));
            break;
        }
    }

    return totalValue;
}

int main() {
    vector<Item> items = {
        {60, 10},
        {100, 20},
        {120, 30}
    };

    int capacity = 50;

    cout << fractionalKnapsack(items, capacity) << endl;

    return 0;
}