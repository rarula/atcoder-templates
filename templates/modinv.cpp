#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
ll modinv(ll a, ll mod) {
    ll b = mod;
    ll u = 1;
    ll v = 0;
    while (b) {
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

/*

// from https://github.com/rarula/atcoder-templates
ll modinv(ll a, ll mod) {
    return modpow(a, mod-2, mod);
}

*/
