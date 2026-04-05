#include <bits/stdc++.h>
using namespace std;

long long merge(vector<int>& data, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(n1);
    vector<int> right(n2);

    for (int i = 0; i < n1; i++) left[i] = data[low + i];
    for (int i = 0; i < n2; i++) right[i] = data[mid + 1 + i];

    int i = 0, j = 0, k = low;
    long long invCount = 0;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            data[k++] = left[i++];
        } else {
            data[k++] = right[j++];
            invCount += (n1 - i);
        }
    }

    while (i < n1) data[k++] = left[i++];
    while (j < n2) data[k++] = right[j++];

    return invCount;
}

long long mergesort(vector<int>& data, int low, int high) {
    if (low >= high) return 0;

    int mid = low + (high - low) / 2;
    long long invCount = 0;

    invCount += mergesort(data, low, mid);
    invCount += mergesort(data, mid + 1, high);
    invCount += merge(data, low, mid, high);

    return invCount;
}

int main() {
    vector<int> data = {2, 10, 5, 1, -10};

    long long inversions = mergesort(data, 0, data.size() - 1);

    cout << "Sorted array: ";
    for (int x : data) cout << x << " ";
    cout << "\nInversion count: " << inversions << endl;

    return 0;
}