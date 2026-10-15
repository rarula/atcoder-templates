#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
struct Int128 {
    using i128 = __int128_t;
    i128 v;

    Int128() : v(0) {}
    Int128(i128 v) : v(v) {}
    Int128(const string &str) : v(0) { parse(str); }

    void parse(const string &str) {
        v = 0;
        for (const char chr : str) {
            if ('0' <= chr && chr <= '9') {
                v *= 10;
                v += chr - '0';
            }
        }
        if (str[0] == '-') v *= -1;
    }

    string get_string() {
        string res = "";
        i128 num = v;

        bool negative = false;
        if (num < 0) {
            negative = true;
            num *= -1;
        }
        do {
            res += char((num % 10) + '0');
            num /= 10;
        } while ((num > 0));
        if (negative) res += '-';

        reverse(res.begin(), res.end());
        return res;
    }

    // 複合代入算術演算子
    Int128& operator+=(const Int128 &r) { v += r.v; return *this; }
    Int128& operator-=(const Int128 &r) { v -= r.v; return *this; }
    Int128& operator*=(const Int128 &r) { v *= r.v; return *this; }
    Int128& operator/=(const Int128 &r) { v /= r.v; return *this; }
    Int128& operator%=(const Int128 &r) { v %= r.v; return *this; }

    // 複合代入ビット演算子
    Int128& operator<<=(const Int128 &r) { v <<= r.v; return *this; }
    Int128& operator>>=(const Int128 &r) { v >>= r.v; return *this; }
    Int128& operator&= (const Int128 &r) { v &= r.v; return *this; }
    Int128& operator^= (const Int128 &r) { v ^= r.v; return *this; }
    Int128& operator|= (const Int128 &r) { v |= r.v; return *this; }

    // 単項演算子 (前置形式)
    Int128 operator~() const { Int128 res = *this; res.v = ~res.v; return res; }
    Int128 operator+() const { return Int128(*this); }
    Int128 operator-() const { return Int128(0) - Int128(*this); }
    Int128& operator++() { ++v; return *this; }
    Int128& operator--() { --v; return *this; }

    // 単項演算子 (後置形式)
    Int128 operator++(int) { Int128 res = *this; ++(*this); return res; }
    Int128 operator--(int) { Int128 res = *this; --(*this); return res; }

    // 算術演算子
    friend Int128 operator+(const Int128 &l, const Int128 &r) { return Int128(l) += r; }
    friend Int128 operator-(const Int128 &l, const Int128 &r) { return Int128(l) -= r; }
    friend Int128 operator*(const Int128 &l, const Int128 &r) { return Int128(l) *= r; }
    friend Int128 operator/(const Int128 &l, const Int128 &r) { return Int128(l) /= r; }
    friend Int128 operator%(const Int128 &l, const Int128 &r) { return Int128(l) %= r; }

    // ビット演算子
    friend Int128 operator<<(const Int128 &l, const Int128 &r) { return Int128(l) <<= r; }
    friend Int128 operator>>(const Int128 &l, const Int128 &r) { return Int128(l) >>= r; }
    friend Int128 operator& (const Int128 &l, const Int128 &r) { return Int128(l) &= r; }
    friend Int128 operator^ (const Int128 &l, const Int128 &r) { return Int128(l) ^= r; }
    friend Int128 operator| (const Int128 &l, const Int128 &r) { return Int128(l) |= r; }

    // 比較演算子
    friend bool operator==(const Int128 &l, const Int128 &r) { return l.v == r.v; }
    friend bool operator!=(const Int128 &l, const Int128 &r) { return l.v != r.v; }
    friend bool operator<=(const Int128 &l, const Int128 &r) { return l.v <= r.v; }
    friend bool operator>=(const Int128 &l, const Int128 &r) { return l.v >= r.v; }
    friend bool operator< (const Int128 &l, const Int128 &r) { return l.v < r.v; }
    friend bool operator> (const Int128 &l, const Int128 &r) { return l.v > r.v; }

    // 標準入出力
    friend istream& operator>>(istream& is, Int128 &val) {
        string str;
        cin >> str;
        val.parse(str);
        return is;
    }
    friend ostream& operator<<(ostream& os, Int128 val) {
        return os << val.get_string();
    }
};
