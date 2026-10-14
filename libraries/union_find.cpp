#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
// Union-Find (union by size + path compression)
struct UnionFind {
    vector<int> parents;
    vector<int> sizes;

    /// @brief n 頂点 0 辺の無向グラフを作ります。計算量は O(n) 。
    /// @param n 頂点数 (0 ≤ n ≤ 10^8)
    UnionFind(int n) : parents(n), sizes(n, 1) {
        for (int i = 0; i < n; i++) parents[i] = i;
    }

    /// @brief 頂点 a の属する連結成分の代表元を返します。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @return 頂点 a の属する連結成分の代表元
    int leader(int a) {
        if (parents[a] == a) return a;
        return parents[a] = leader(parents[a]);
    }

    /// @brief 頂点 a, b が連結かどうかを返します。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @param b 対象の頂点 (0 ≤ b < n)
    /// @return 頂点 a, b が連結ならば `true` 、そうでないなら `false`
    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    /// @brief 辺 (a, b) を加えます。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @param b 対象の頂点 (0 ≤ b < n)
    void merge(int a, int b) {
        int al = leader(a);
        int bl = leader(b);
        if (al == bl) return;
        if (sizes[bl] < sizes[al]) swap(al, bl);
        parents[al] = bl;
        sizes[bl] += sizes[al];
    }

    /// @brief 頂点 a の属する連結成分のサイズを返します。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @return 頂点 a の属する連結成分のサイズ
    int size(int a) {
        return sizes[leader(a)];
    }
};
