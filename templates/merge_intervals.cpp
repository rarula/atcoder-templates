#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 整数の両閉区間 [l, r] において重なる・隣接する区間をマージした列を返す
vector<pair<ll,ll>> merge_intervals(vector<pair<ll,ll>> vec) {
    ll len = vec.size();
    if (len == 0) return vector<pair<ll,ll>>();
    sort(vec.begin(), vec.end());

    vector<pair<ll,ll>> res;
    res.push_back(vec[0]);
    for (int i = 1; i < len; i++) {
        auto& [l, r] = res.back();
        auto [nl, nr] = vec[i];
        if (nl <= r + 1) { // この箇所で、例えば [2, 5] と [6, 8] はマージされて [2, 8] となることに注意する
            r = max(r, nr);
        } else {
            res.push_back(vec[i]);
        }
    }
    return res;
}
