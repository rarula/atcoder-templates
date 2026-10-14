#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/// @brief Weighted Union-Find (union by size + path compression)
/// @tparam T `+`, `-`, `+=`, `-=` が定義された加法群
template<class T> struct WeightedUnionFind {
    vector<int> parents;
    vector<int> sizes;
    vector<T> weight_diff;

    /// @brief n 頂点 0 辺の無向グラフを作ります。計算量は O(n) 。
    /// @param n 頂点数 (0 ≤ n)
    /// @param e 重みとなる加法群に対する単位元
    WeightedUnionFind(int n, T e) : parents(n), sizes(n, 1), weight_diff(n, e) {
        for (int i = 0; i < n; i++) parents[i] = i;
    }

    /// @brief 頂点 a の属する連結成分の代表元を返します。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @return 頂点 a の属する連結成分の代表元
    int leader(int a) {
        if (parents[a] == a) return a;
        int l = leader(parents[a]);
        weight_diff[a] += weight_diff[parents[a]];
        return parents[a] = l;
    }

    /// @brief 頂点 a, b が連結かどうかを返します。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @param b 対象の頂点 (0 ≤ b < n)
    /// @return 頂点 a, b が連結ならば `true` 、そうでないなら `false`
    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    /// @brief
    /// 頂点 a, b を weight(b) - weight(a) = w となるように連結します。@n
    /// 頂点 a, b が既に連結のとき何もしません。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @param b 対象の頂点 (0 ≤ b < n)
    /// @param w weight(b) - weight(a) = w となる重み w
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

    /// @brief 頂点 a の属する連結成分のサイズを返します。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @return 頂点 a の属する連結成分のサイズ
    int size(int a) {
        return sizes[leader(a)];
    }

    /// @brief 頂点 a の重みを返します。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @return 頂点 a の重み
    T weight(int a) {
        leader(a);
        return weight_diff[a];
    }

    /// @brief
    /// 頂点 a, b が連結のとき weight(b) - weight(a) を返します。@n
    /// 頂点 a, b が連結でないときの動作は未定義です。計算量は ならし O(α(n)) 。
    /// @param a 対象の頂点 (0 ≤ a < n)
    /// @param b 対象の頂点 (0 ≤ b < n)
    /// @return weight(b) - weight(a)
    T diff(int a, int b) {
        return weight(b) - weight(a);
    }
};
