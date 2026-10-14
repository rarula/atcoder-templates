#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
template<class S, S (*op)(S, S), S (*e)()>
struct Segtree {
private:
    int n; // 元の要素数
    int size; // n以上で最小の2べき
    int log; // 根から葉までの層の差
    vector<S> data;

    void update_node(int p) {
        data[p] = op(data[2*p], data[2*p+1]);
    }

public:
    Segtree(int n) : n(n) {
        size = 1;
        log = 0;
        while (size < n) {
            size *= 2;
            log++;
        }
        data.resize(2 * size, e());
    }

    Segtree(const vector<S>& seq) : Segtree(seq.size()) {
        for (int i = 0; i < n; i++) data[size+i] = seq[i];
        for (int i = size-1; i >= 1; i--) update_node(i);
    }

    void set(int p, S val) {
        assert(0 <= p && p < n);
        p += size;
        data[p] = val;
        for (int i = 1; i <= log; i++) update_node(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < n);
        return data[p + size];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return e();
        l += size;
        r += size;
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

    S all_prod() const {
        return data[1];
    }
};
