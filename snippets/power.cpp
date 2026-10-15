#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll power(ll a, ll n) {
    ll res = 1;
    for (int i = 0; i < n; i++) res *= a;
    return res;
}
