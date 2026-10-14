#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll ceildiv(ll a, ll b) {
    assert(b != 0);
    ll q = a / b;
    ll r = a % b;
    if (r != 0 && ((a > 0) == (b > 0))) q++;
    return q;
}
