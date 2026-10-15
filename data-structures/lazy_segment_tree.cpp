#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
template<class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct LazySegtree {
private:
    int n; // 元の要素数
    int size; // n以上で最小の2べき
    int log; // 根から葉までの層の差
    vector<S> data;
    vector<F> lazy;

    void update_node(int p) {
        data[p] = op(data[2*p], data[2*p+1]);
    }

    void apply_node(int p, F f) {
        data[p] = mapping(f, data[p]);
        if (p < size) lazy[p] = composition(f, lazy[p]);
    }

    void push(int p) {
        apply_node(2*p+0, lazy[p]);
        apply_node(2*p+1, lazy[p]);
        lazy[p] = id();
    }

public:
    // 長さ n の配列を作る。初期値はすべて e() 。
    // O(n)
    LazySegtree(int n) : n(n) {
        size = 1;
        log = 0;
        while (size < n) {
            size *= 2;
            log++;
        }
        data.resize(2 * size, e());
        lazy.resize(1 * size, id());
    }

    // 長さ seq.size() の配列を作る。初期値は seq に基づいた値になる。
    // O(n)
    LazySegtree(const vector<S>& seq) : LazySegtree(seq.size()) {
        for (int i = 0; i < n; i++) data[size+i] = seq[i];
        for (int i = size-1; i >= 1; i--) update_node(i);
    }

    // p 番目の値を val に更新する
    // O(log n)
    void set(int p, S val) {
        assert(0 <= p && p < n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        data[p] = val;
        for (int i = 1; i <= log; i++) update_node(p >> i);
    }

    // p 番目の値を返す
    // O(log n)
    S get(int p) {
        assert(0 <= p && p < n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return data[p];
    }

    // 区間 [l, r) の値のモノイド積を返す
    // O(log n)
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return e();
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e();
        S smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, data[l++]);
            if (r & 1) smr = op(data[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    // 区間 [0, n) の値のモノイド積を返す
    // O(1)
    S all_prod() const {
        return data[1];
    }

    // p 番目の値を作用 f で更新する
    // O(log n)
    void apply(int p, F f) {
        assert(0 <= p && p < n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        apply_node(p, f);
        for (int i = 1; i <= log; i++) update_node(p >> i);
    }

    // 区間 [l, r) の値を作用 f で更新する
    // O(log n)
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n);
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int nl = l;
        int nr = r;
        while (nl < nr) {
            if (nl & 1) apply_node(nl++, f);
            if (nr & 1) apply_node(--nr, f);
            nl >>= 1;
            nr >>= 1;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update_node(l >> i);
            if (((r >> i) << i) != r) update_node((r - 1) >> i);
        }
    }
};
