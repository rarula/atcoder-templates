#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
namespace geometry2i {
    using T = ll;
    using F = long double;

    struct vec {
        T x, y;
        T norm2() const {
            return x*x + y*y;
        }
        F norm() const {
            return sqrtl(norm2());
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
        vec operator+() const {
            return vec(*this);
        }
        vec operator-() const {
            return vec(-x, -y);
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

    T dot(const vec& a, const vec& b) {
        return a.x*b.x + a.y*b.y;
    }
    T cross(const vec& a, const vec& b) {
        return a.x*b.y - a.y*b.x;
    }

    struct line {
        vec s, t;
        vec dir() const {
            return t - s;
        }

        line(vec s = vec(), vec t = vec()) : s(s), t(t) {}

        // +1 : (点sを基準に) st から見て tp が 反時計回り に曲がるとき
        // -1 : (点sを基準に) st から見て tp が 時計回り に曲がるとき
        // +2 : 点 t, s, p がこの順番で 同一直線上 にあるとき
        // -2 : 点 s, t, p がこの順番で 同一直線上 にあるとき
        //  0 : 点 s, p, t がこの順番で 同一直線上 にあるとき
        int ccw(const vec& p) const {
            if (cross(dir(), p - s) > 0) return +1;
            if (cross(dir(), p - s) < 0) return -1;
            if (dot(dir(), p - s) < 0) return +2;
            if (dot(dir(), t - p) < 0) return -2;
            return 0;
        }

        friend istream& operator>>(istream& is, line& l) {
            is >> l.s >> l.t;
            return is;
        }
    };

    struct segment : line {
        segment(vec s = vec(), vec t = vec()) : line(s, t) {}
    };

    bool is_parallel(const vec& a, const vec& b) {
        return cross(a, b) == 0;
    }
    bool is_orthogonal(const vec& a, const vec& b) {
        return dot(a, b) == 0;
    }

    bool intersect(const line& l, const vec& p) {
        return abs(l.ccw(p)) != 1;
    }
    bool intersect(const line& a, const line& b) {
        return !is_parallel(a.dir(), b.dir());
    }
    bool intersect(const segment& s, const vec& p) {
        return s.ccw(p) == 0;
    }
    bool intersect(const segment& a, const segment& b) {
        return a.ccw(b.s) * a.ccw(b.t) <= 0 && b.ccw(a.s) * b.ccw(a.t) <= 0;
    }

    F distance(const vec& a, const vec& b) {
        return (b - a).norm();
    }
    F distance(const line& l, const vec& p) {
        return abs(cross(l.dir(), p - l.s) / l.dir().norm());
    }
    F distance(const line& a, const line& b) {
        if (intersect(a, b)) return 0;
        return distance(a, b.s);
    }
    F distance(const segment& s, const vec& p) {
        if (dot(s.t - s.s, p - s.s) < 0) return distance(s.s, p);
        if (dot(s.s - s.t, p - s.t) < 0) return distance(s.t, p);
        return distance(static_cast<line>(s), p);
    }
    F distance(const segment& a, const segment& b) {
        if (intersect(a, b)) return 0;
        return min({ distance(a, b.s), distance(a, b.t), distance(b, a.s), distance(b, a.t) });
    }
}
using namespace geometry2i;
