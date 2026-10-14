#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
ll totient(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            res /= p;
            res *= p - 1;
            do {
                n /= p;
            } while (n % p == 0);
        }
    }
    if (n != 1) {
        res /= n;
        res *= n - 1;
    }
    return res;
}
