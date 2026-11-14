#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
namespace geometry2f {
    using T = double;
    const T eps = 1e-9;

    bool equal(T a, T b) {
        return abs(a - b) < eps;
    }

    struct vec {
        T x, y;
        T norm2() const {
            return x*x + y*y;
        }
        T norm() const {
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
            if (cross(dir(), p - s) > eps) return +1;
            if (cross(dir(), p - s) < -eps) return -1;
            if (dot(dir(), p - s) < -eps) return +2;
            if (dot(dir(), t - p) < -eps) return -2;
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
        return equal(cross(a, b), 0.0);
    }
    bool is_orthogonal(const vec& a, const vec& b) {
        return equal(dot(a, b), 0.0);
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

    vec crosspoint(const line& a, const line& b) {
        assert(intersect(a, b));
        T s1 = cross(b.t - a.s, b.dir());
        T s2 = cross(a.dir(), b.dir());
        return a.s + a.dir() * abs(s1 / s2);
    }
    vec crosspoint(const segment& a, const segment& b) {
        assert(intersect(a, b));
        return crosspoint(static_cast<line>(a), static_cast<line>(b));
    }

    T distance(const vec& a, const vec& b) {
        return (b - a).norm();
    }
    T distance(const line& l, const vec& p) {
        return abs(cross(l.dir(), p - l.s) / l.dir().norm());
    }
    T distance(const line& a, const line& b) {
        if (intersect(a, b)) return 0;
        return distance(a, b.s);
    }
    T distance(const segment& s, const vec& p) {
        if (dot(s.t - s.s, p - s.s) < eps) return distance(s.s, p);
        if (dot(s.s - s.t, p - s.t) < eps) return distance(s.t, p);
        return distance(static_cast<line>(s), p);
    }
    T distance(const segment& a, const segment& b) {
        if (intersect(a, b)) return 0;
        return min({ distance(a, b.s), distance(a, b.t), distance(b, a.s), distance(b, a.t) });
    }

    using polygon = vector<vec>;

    bool is_convex(const polygon& g) {
        int size = g.size();
        for (int i = 0; i < size; i++) {
            if (line(g[i], g[(i + 1) % size]).ccw(g[(i + 2) % size]) == -1) return false;
        }
        return true;
    }

    T signed_area(const polygon& g) {
        T s = 0;
        int size = g.size();
        for (int i = 0; i < size; i++) {
            s += cross(g[i], g[(i + 1) % size]);
        }
        return s / 2.0;
    }

    T area(const polygon& g) {
        return abs(signed_area(g));
    }
}
using namespace geometry2f;
