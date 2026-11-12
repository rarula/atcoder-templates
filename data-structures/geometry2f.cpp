#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
namespace geometry2f {
    using T = double;

    struct vec {
        T x, y;
        T norm2() const {
            return x*x + y*y;
        }

        vec(T x = 0, T y = 0) : x(x), y(y) {}
        vec& operator+=(const vec& v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        vec& operator-=(const vec& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        vec& operator*=(T s) {
            x *= s;
            y *= s;
            return *this;
        }
        vec& operator/=(T s) {
            x /= s;
            y /= s;
            return *this;
        }

        friend vec operator+(const vec& l, const vec& r) {
            return vec(l) += r;
        }
        friend vec operator-(const vec& l, const vec& r) {
            return vec(l) -= r;
        }
        friend vec operator*(const vec& l, T r) {
            return vec(l) *= r;
        }
        friend vec operator*(T r, const vec& l) {
            return vec(l) *= r;
        }
        friend vec operator/(const vec& l, T r) {
            return vec(l) /= r;
        }
        friend vec operator/(T r, const vec& l) {
            return vec(l) /= r;
        }
        friend istream& operator>>(istream& is, vec& v) {
            is >> v.x >> v.y;
            return is;
        }
    };

    struct line {
        vec s, t;
        line(vec s = vec(), vec t = vec()) : s(s), t(t) {}
        friend istream& operator>>(istream& is, line& l) {
            is >> l.s >> l.t;
            return is;
        }
    };

    T dot(const vec& a, const vec& b) {
        return a.x*b.x + a.y*b.y;
    }

    vec projection(const line& l, const vec& p) {
        vec sp = p - l.s;
        vec st = l.t - l.s;
        return l.s + (dot(sp, st) / st.norm2()) * st;
    }

    vec reflection(const line& l, const vec& p) {
        vec q = projection(l, p);
        vec pq = q - p;
        return q + pq;
    }
}
using namespace geometry2f;
