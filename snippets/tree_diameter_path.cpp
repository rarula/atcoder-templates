#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
// 木の直径（その木の単純パスに含まれる辺の本数のうち最大のもの）と、直径をなす単純パスをひとつ見つけて返す
pair<ll,vector<ll>> tree_diameter_path(const ll n, const vector<vector<ll>>& g) {
    vector<ll> from(n);
    using P = pair<ll,ll>; // dist, v
    auto dfs = [&](auto self, ll v, ll prev, ll dist) -> P {
        from[v] = prev;
        P res = make_pair(dist, v);
        for (auto nv : g[v]) {
            if (nv == prev) continue;
            res = max(res, self(self, nv, v, dist+1));
        }
        return res;
    };
    auto [_, a] = dfs(dfs, 0, -1, 0);
    auto [d, b] = dfs(dfs, a, -1, 0);
    vector<ll> path;
    while (b != -1) {
        path.push_back(b);
        b = from[b];
    }
    return make_pair(d, path);
}
