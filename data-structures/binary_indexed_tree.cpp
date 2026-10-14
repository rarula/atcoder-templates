#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
template<class T> struct BIT {
private:
    int n;
    vector<T> data;

    T sum(int r) {
        assert(0 <= r && r <= n);
        T res = 0;
        while (r > 0) {
            res += data[r];
            r -= r & -r;
        }
        return res;
    }

public:
    BIT(int n) : n(n), data(n + 1) {}

    void add(int p, T val) {
        assert(0 <= p && p < n);
        p++;
        while (p <= n) {
            data[p] += val;
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }
};
