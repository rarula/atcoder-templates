#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
    ll x;
    ll y;
};

ll cross(const Point& a, const Point& b) {
    return a.x * b.y - b.x * a.y;
}

bool cmp(const Point& a, const Point& b) {
    bool isTopA = a.y > 0 || (a.y == 0 && a.x > 0);
    bool isTopB = b.y > 0 || (b.y == 0 && b.x > 0);
    if (isTopA != isTopB) return !isTopA && isTopB;
    return cross(a, b) > 0;
}

void polar_angle_sort(vector<Point> &points) {
    sort(points.begin(), points.end(), cmp);
}
