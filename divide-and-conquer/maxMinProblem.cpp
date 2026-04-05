#include <iostream>
using namespace std;

struct Pair {
    int max;
    int min;
};

Pair findMaxMin(int a[], int low, int high) {
    Pair result, left, right;
    int mid;

    if (low == high) {
        result.min = a[low];
        result.max = a[high];
        return result;
    }

    if (high == low + 1) {
        if (a[low] < a[high]) {
            result.min = a[low];
            result.max = a[high];
        } else {
            result.min = a[high];
            result.max = a[low];
        }
        return result;
    }

    mid = low + (high - low) / 2;

    left = findMaxMin(a, low, mid);
    right = findMaxMin(a, mid + 1, high);

    result.min = (left.min < right.min) ? left.min : right.min;
    result.max = (left.max > right.max) ? left.max : right.max;

    return result;
}

int main() {
    int a[] = {6, 4, 26, 14, 33, 64, 46};
    int n = sizeof(a) / sizeof(a[0]);

    Pair result = findMaxMin(a, 0, n - 1);

    cout << "min: " << result.min << endl;
    cout << "max: " << result.max << endl;
    
    return 0;
}