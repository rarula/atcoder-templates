#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "modpow.cpp"

// from https://github.com/rarula/atcoder-templates
ll moddiv(ll a, ll b, ll mod) {
    return (a * modpow(b, mod-2, mod)) % mod;
}
