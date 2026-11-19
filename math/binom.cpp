#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
const ll MAX = 1e7; // クエリで飛んでくる可能性のある最大の n,k 以上の値
const ll MOD = 998244353; // MOD は素数かつ MAX < MOD を満たす必要がある
ll fac[MAX + 1], fac_inv[MAX + 1], inv[MAX + 1];
bool binom_init_done = false;

void binom_init() {
    fac[0] = fac_inv[0] = 1;
    fac[1] = fac_inv[1] = 1;
    inv[1] = 1;
    for (ll i = 2; i <= MAX; i++) {
        fac[i] = fac[i-1] * i % MOD;
        inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
        fac_inv[i] = fac_inv[i-1] * inv[i] % MOD;
    }
    binom_init_done = true;
}

ll binom(ll n, ll k) {
    assert(binom_init_done);
    if (n < 0 || k < 0 || n < k) return 0;
    assert(n <= MAX);
    ll a = fac[n];
    ll b = fac_inv[k] * fac_inv[n-k] % MOD;
    return a * b % MOD;
}
