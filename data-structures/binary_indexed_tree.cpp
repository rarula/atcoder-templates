#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
template<class T>
struct BIT {
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
    // 長さ n の配列を作る。初期値はすべて 0 。
    // O(n)
    BIT(int n) : n(n), data(n + 1) {}

    // p 番目の値に val を加算する
    // O(log n)
    void add(int p, T val) {
        assert(0 <= p && p < n);
        p++;
        while (p <= n) {
            data[p] += val;
            p += p & -p;
        }
    }

    // 区間 [l, r) の総和を返す
    // O(log n)
    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }
};
