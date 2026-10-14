#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// next[i][c] := 文字列 s の i 文字目を含めたそれ以降で、文字 c が出現する最小の添え字 (存在しないときは -1)
vector<vector<ll>> make_next(const string &s) {
    ll n = s.size();
    vector<vector<ll>> res(n+1, vector<ll>(26, -1));
    for (int i = n-1; i >= 0; i--) {
        res[i] = res[i+1];
        res[i][s[i] - 'a'] = i; // 英子文字 a~z にのみ対応 (英大文字 A~Z に対応するには 'A' に変更)
    }
    return res;
}
