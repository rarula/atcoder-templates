#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 区間をsetで管理するためのデータ構造（右半開区間）
struct IntervalSet {
private:
    using T = ll;
    struct Interval {
        T l;
        T r;
        explicit Interval(const T &l, const T &r) : l(l), r(r) {}
        bool operator<(const Interval &another) const {
            if (l == another.l) {
                return r < another.r;
            } else {
                return l < another.l;
            }
        }
        friend ostream& operator<<(ostream &os, const Interval &e) {
            return os << "[" << e.l << "," << e.r << ")";
        }
    };
    set<Interval> s;

    /// 処理中に区間 [l, r) を挿入したときに呼び出される。
    void on_insert(T l, T r) {
        // Todo
    }

    /// 処理中に区間 [l, r) を削除したときに呼び出される。
    void on_erase(T l, T r) {
        // Todo
    }

    void insert_wrapper(T l, T r) {
        on_insert(l, r);
        s.insert(Interval(l, r));
    }

    set<Interval>::iterator insert_wrapper(const set<Interval>::iterator& it, T l, T r) {
        on_insert(l, r);
        return s.insert(it, Interval(l, r));
    }

    set<Interval>::iterator erase_wrapper(const set<Interval>::iterator& it) {
        on_erase(it->l, it->r);
        return s.erase(it);
    }

public:
    /// 区間 [l, r) を挿入します。
    void insert(T l, T r) {
        auto it = s.lower_bound(Interval(l, 0));
        while (it != s.end()) {
            T sl = it->l;
            T sr = it->r;
            if (sl <= r) { // l <= sl <= r が成り立つとき
                if (sr <= r) { // l <= sl <= sr <= r が成り立つとき
                    it = erase_wrapper(it);
                }
                else { // l <= sl <= r < sr が成り立つとき
                    r = sr;
                    it = erase_wrapper(it);
                }
            }
            else { // l <= r < sl が成り立つとき
                break;
            }
        }
        if (it != s.begin()) {
            it--;
            T sl = it->l;
            T sr = it->r;
            if (l <= sr) { // sl <= l <= sr が成り立つとき
                l = sl;
                r = max(r, sr);
                it = erase_wrapper(it);
            }
        }
        insert_wrapper(l, r);
    }

    /// 区間 [l, r) を削除します。
    void erase(T l, T r) {
        auto it = s.lower_bound(Interval(l, 0));
        while (it != s.end()) {
            T sl = it->l;
            T sr = it->r;
            if (sl < r) { // l <= sl < r が成り立つとき
                if (sr <= r) { // sl < r かつ l <= sl <= sr <= r が成り立つとき
                    it = erase_wrapper(it);
                }
                else { // l <= sl <= r < sr が成り立つとき
                    it = erase_wrapper(it);
                    it = insert_wrapper(it, r, sr);
                }
            }
            else { // l <= r <= sl が成り立つとき
                break;
            }
        }
        if (it != s.begin()) {
            it--;
            T sl = it->l;
            T sr = it->r;
            if (l < sr) { // sl <= l < sr が成り立つとき
                if (r < sr) { // sl <= l <= r < sr が成り立つとき
                    it = erase_wrapper(it);
                    insert_wrapper(sl, l);
                    insert_wrapper(r, sr);
                }
                else { // sl <= l <= sr <= r が成り立つとき
                    it = erase_wrapper(it);
                    insert_wrapper(sl, l);
                }
            }
        }
    }

    /// 区間 [l, r) を完全に含む区間が存在するか探索します。
    bool contains(const T &l, const T &r) const {
        auto it = s.upper_bound(Interval(l, numeric_limits<T>::max()));
        if (it != s.begin()) {
            it--;
            T sl = it->l;
            T sr = it->r;
            if (sl <= l && r <= sr) return true;
        }
        return false;
    }

    /// p 以上であって、いずれの区間にも含まれない最小の整数を返します。
    T mex(const T &p) const {
        auto it = s.upper_bound(Interval(p, numeric_limits<T>::max()));
        if (it != s.begin()) {
            it--;
            T sl = it->l;
            T sr = it->r;
            if (sl <= p && p < sr) return sr;
        }
        return p;
    }

    /// 区間の集合の先頭要素を指すイテレータを返します。
    set<Interval>::iterator begin() const {
        return s.begin();
    }

    /// 区間の集合の終端（≠末尾）要素を指すイテレータを返します。
    set<Interval>::iterator end() const {
        return s.end();
    }

    friend ostream& operator<<(ostream &os, const IntervalSet &e) {
        for (const auto& interval : e.s) os << interval << "  ";
        return os;
    }
};
