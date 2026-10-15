#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
const ll MAX = 1e7; // クエリで飛んでくる可能性のある最大の n,k 以上の値
const ll MOD = 998244353; // 法 M の値 (M は素数かつ、常に n < M を満たさなければならない)
ll fac[MAX], fac_inv[MAX], inv[MAX];

void binom_init() {
    fac[0] = fac_inv[0] = 1;
    fac[1] = fac_inv[1] = 1;
    inv[1] = 1;
    for (ll i = 2; i < MAX; i++) {
        fac[i] = fac[i-1] * i % MOD;
        inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
        fac_inv[i] = fac_inv[i-1] * inv[i] % MOD;
    }
}

ll binom(ll n, ll k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    ll a = fac[n];
    ll b = fac_inv[k] * fac_inv[n-k] % MOD;
    return a * b % MOD;
}
