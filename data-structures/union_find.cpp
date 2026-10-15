#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
struct UnionFind {
    vector<int> parent;
    vector<int> siz;

    // n 頂点 0 辺の無向グラフを作る
    // O(n)
    UnionFind(int n) : parent(n), siz(n, 1) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // 頂点 a の属する連結成分の代表元の頂点番号を返す
    // O(α(n))
    int leader(int a) {
        if (parent[a] == a) return a;
        return parent[a] = leader(parent[a]);
    }

    // 頂点 a, b が連結なら true、連結でないなら false を返す
    // O(α(n))
    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    // 頂点 a, b を結ぶ辺を加える
    // O(α(n))
    void merge(int a, int b) {
        int al = leader(a);
        int bl = leader(b);
        if (al == bl) return;
        if (siz[bl] < siz[al]) swap(al, bl);
        parent[al] = bl;
        siz[bl] += siz[al];
    }

    // 頂点 a の属する連結成分のサイズを返す
    // O(α(n))
    int size(int a) {
        return siz[leader(a)];
    }
};
