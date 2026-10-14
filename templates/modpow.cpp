#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll modpow(ll a, ll n, ll mod) {
    a %= mod;
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}
