#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
template<ll M> struct modint {
    ll v = 0;
    ll val() const {
        return v;
    }
    modint(ll v = 0) : v((v % M + M) % M) {}
    modint operator+() const {
        return *this;
    }
    modint operator-() const {
        return modint() - *this;
    }
    modint& operator+=(const modint &r) {
        if ((v += r.v) >= M) v -= M;
        return *this;
    }
    modint& operator-=(const modint &r) {
        if ((v += M - r.v) >= M) v -= M;
        return *this;
    }
    modint& operator*=(const modint &r) {
        v *= r.v;
        v %= M;
        return *this;
    }
    modint& operator/=(const modint &r) {
        return *this *= r.inv();
    }
    modint& operator++() {
        (*this) += 1;
        return *this;
    }
    modint& operator--() {
        (*this) -= 1;
        return *this;
    }
    modint operator++(int) {
        modint res = *this;
        ++(*this);
        return res;
    }
    modint operator--(int) {
        modint res = *this;
        --(*this);
        return res;
    }
    modint pow(ll n) const {
        modint x = *this;
        modint res = 1;
        while (n > 0) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }
    modint inv() const {
        return pow(M-2);
    }
    friend modint operator+(const modint &l, const modint &r) {
        return modint(l) += r;
    }
    friend modint operator-(const modint &l, const modint &r) {
        return modint(l) -= r;
    }
    friend modint operator*(const modint &l, const modint &r) {
        return modint(l) *= r;
    }
    friend modint operator/(const modint &l, const modint &r) {
        return modint(l) /= r;
    }
    friend bool operator==(const modint &l, const modint &r) {
        return l.v == r.v;
    }
    friend bool operator!=(const modint &l, const modint &r) {
        return l.v != r.v;
    }
};
using mint = modint<998244353>;
