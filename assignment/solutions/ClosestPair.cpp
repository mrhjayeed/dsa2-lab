#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(vector<Point>& pts, int l, int r) {
    double minDist = DBL_MAX;

    for (int i = l; i < r; i++)
        for (int j = i + 1; j < r; j++)
            minDist = min(minDist, dist(pts[i], pts[j]));

    return minDist;
}

double stripClosest(vector<Point>& strip, double d) {
    double minDist = d;
    int n = strip.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n &&
             (strip[j].y - strip[i].y) < minDist; j++) {
            minDist = min(minDist, dist(strip[i], strip[j]));
        }
    }
    return minDist;
}

double closestUtil(vector<Point>& Px, vector<Point>& Py) {
    int n = Px.size();

    if (n <= 3)
        return bruteForce(Px, 0, n);

    int mid = n / 2;
    Point midPoint = Px[mid];

    vector<Point> Pxl(Px.begin(), Px.begin() + mid);
    vector<Point> Pxr(Px.begin() + mid, Px.end());

    vector<Point> Pyl, Pyr;
    for (auto& p : Py) {
        if (p.x <= midPoint.x)
            Pyl.push_back(p);
        else
            Pyr.push_back(p);
    }

    double dl = closestUtil(Pxl, Pyl);
    double dr = closestUtil(Pxr, Pyr);

    double d = min(dl, dr);

    vector<Point> strip;
    for (auto& p : Py) {
        if (abs(p.x - midPoint.x) < d)
            strip.push_back(p);
    }

    return min(d, stripClosest(strip, d));
}

double closest(vector<Point>& points) {
    vector<Point> Px = points;
    vector<Point> Py = points;

    sort(Px.begin(), Px.end(), [](Point a, Point b) {
        return a.x < b.x;
    });

    sort(Py.begin(), Py.end(), [](Point a, Point b) {
        return a.y < b.y;
    });

    return closestUtil(Px, Py);
}

int main() {
    vector<Point> points = {
        {2, 3}, {12, 30}, {40, 50},
        {5, 1}, {12, 10}, {3, 4}
    };

    cout << fixed << setprecision(6);
    cout << "Minimum distance = " << closest(points);

    return 0;
}