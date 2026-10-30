#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
struct Xorshift128 {
    using u32 = uint32_t;
    u32 x = 123456789;
    u32 y = 362436069;
    u32 z = 521288629;
    u32 w = 88675123;

    // [0, 2^32) の範囲内の整数を返す
    u32 next() {
        u32 t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    // [0, n) の範囲内の整数を返す
    int next_int(int n) {
        return next() % n;
    }

    // [0, 1) の範囲内の実数を返す
    double next_double() {
        return next() * (1.0 / 4294967296.0);
    }
};


// from https://github.com/rarula/atcoder-templates
struct Xorshift64 {
    using u64 = uint64_t;
    u64 a = 13579;
    u64 next() {
        u64 x = a;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        return a = x;
    }
    u64 max_value() {
        return numeric_limits<u64>::max();
    }
};

struct Xorshift32 {
    using u32 = uint32_t;
    u32 a = 13579;
    u32 next() {
        u32 x = a;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        return a = x;
    }
    u32 max_value() {
        return numeric_limits<u32>::max();
    }
};
