#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& data, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(n1);
    vector<int> right(n2);

    for (int i = 0; i < n1; i++) left[i] = data[low + i];
    for (int i = 0; i < n2; i++) right[i] = data[mid + 1 + i];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] < right[j]) {
            data[k] = left[i++];
        } else {
            data[k] = right[j++];
        }
        k++;
    }

    while (i < n1) {
        data[k++] = left[i++];
    }

    while (j < n2) {
        data[k++] = right[j++];
    }
}

void mergesort(vector<int>& data, int low, int high) {

    if (low >= high) {
        return;
    }
    int mid = low + (high - low) / 2;

    mergesort(data, low, mid);
    mergesort(data, mid + 1, high);

    merge(data, low, mid, high);
}

int main() {
    vector<int> data = {2, 10, 5, 1, -10};

    mergesort(data, 0, data.size() - 1);

    for (int i : data) cout << i << " ";
    cout << endl;

    return 0;
}