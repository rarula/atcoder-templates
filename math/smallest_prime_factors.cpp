#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "eratosthenes_sieve.cpp"

// from https://github.com/rarula/atcoder-templates
vector<ll> smallest_prime_factors(ll n) {
    vector<ll> spf(n+1, 0);
    auto is_prime = eratosthenes(n);
    for (int p = n; p >= 2; p--) {
        if (!is_prime[p]) continue;
        for (int m = p; m <= n; m += p) {
            spf[m] = p;
        }
    }
    return spf;
}
