#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll floordiv(ll a, ll b) {
    assert(b != 0);
    ll r = (a % b + b) % b;
    return (a - r) / b;
}
