#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
// T には `+`, `-`, `+=`, `-=` が定義された加法群を要求する
template<class T>
struct WeightedUnionFind {
    vector<int> parents;
    vector<int> sizes;
    vector<T> weight_diff;

    // n 頂点 0 辺の無向グラフを作る。 e は T の単位元。
    // O(n)
    WeightedUnionFind(int n, T e) : parents(n), sizes(n, 1), weight_diff(n, e) {
        for (int i = 0; i < n; i++) parents[i] = i;
    }

    // 頂点 a の属する連結成分の代表元の頂点番号を返す
    // O(α(n))
    int leader(int a) {
        if (parents[a] == a) return a;
        int l = leader(parents[a]);
        weight_diff[a] += weight_diff[parents[a]];
        return parents[a] = l;
    }

    // 頂点 a, b が連結なら true、連結でないなら false を返す
    // O(α(n))
    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    // 頂点 a, b を weight(b) - weight(a) = w となるように連結する。頂点 a, b が既に連結のとき何もしない。
    // O(α(n))
    void merge(int a, int b, T w) {
        w = -w;
        w -= weight(a);
        w += weight(b);
        int al = leader(a);
        int bl = leader(b);
        if (al == bl) return;
        if (sizes[bl] < sizes[al]) {
            swap(al, bl);
            w = -w;
        }
        parents[al] = bl;
        sizes[bl] += sizes[al];
        weight_diff[al] = w;
    }

    // 頂点 a の属する連結成分のサイズを返す
    // O(α(n))
    int size(int a) {
        return sizes[leader(a)];
    }

    // 頂点 a の重みを返す
    // O(α(n))
    T weight(int a) {
        leader(a);
        return weight_diff[a];
    }

    // 頂点 a, b が連結のとき weight(b) - weight(a) を返す。頂点 a, b が連結でないときの動作は未定義。
    // O(α(n))
    T diff(int a, int b) {
        return weight(b) - weight(a);
    }
};
