#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
// [L, R] を桁数 d ごとの半開区間 [l, r) に分割し、 f(d, l, r) を呼び出す。
// [L, R] は符号なし整数を要求する。
template<class T, class F> void enumerate_digits(T L, T R, F f) {
    static_assert(std::is_unsigned_v<T>);
    T ok = 1;
    T ng = 10; // [ok, ng)
    for (int d = 1; (d <= 19 && ok <= R); d++) { // unsigned long long を想定して 19 桁まで列挙する (10^19 は unsigned long long に収まるので)
        T l = max(ok, L);
        T r = min(ng, R+1);
        if (l < r) {
            f(d, l, r);
        }
        ok *= 10;
        ng *= 10;
    }
}
