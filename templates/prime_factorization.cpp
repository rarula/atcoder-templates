#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Ret {
    ll p; // p^e = x
    ll e;
    ll x;
    Ret() : p(0), e(0), x(1) {}
    explicit Ret(ll p, ll e, ll x): p(p), e(e), x(x) {}
};

vector<Ret> prime_factorize(ll n) {
    vector<Ret> res;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            ll e = 0;
            ll x = 1;
            while (n % p == 0) {
                n /= p;
                e++;
                x *= p;
            }
            res.push_back(Ret(p, e, x));
        }
    }
    if (n != 1) res.push_back(Ret(n, 1, n));
    return res;
}
