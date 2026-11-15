#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
struct RankedSet {
private:
    using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
    pbds_set s;

public:
    // x を挿入する
    // O(log n)
    void insert(const T& x) {
        s.insert(x);
    }

    // x が存在するなら削除する
    // O(log n)
    void erase(const T& x) {
        s.erase(x);
    }

    // k 番目 (0-indexed) に小さい値を返す
    // O(log n)
    T kth_smallest(int k) const {
        assert(0 <= k && k < size());
        return *s.find_by_order(k);
    }

    // k 番目 (0-indexed) に大きい値を返す
    // O(log n)
    T kth_largest(int k) const {
        assert(0 <= k && k < size());
        return kth_smallest(size() - k - 1);
    }

    // x 未満の値の個数を返す
    // O(log n)
    int count_less(const T& x) const {
        return s.order_of_key(x);
    }

    // x 以下の値の個数を返す
    // O(log n)
    int count_less_equal(const T& x) const {
        return s.order_of_key(x) + (contains(x) ? 1 : 0);
    }

    // x が存在するなら true 、存在しないなら false を返す
    // O(log n)
    bool contains(const T& x) const {
        return s.find(x) != s.end();
    }

    // 要素数を返す
    // O(1)
    int size() const {
        return s.size();
    }

    // 集合が空のとき true 、空でないとき false を返す
    // O(1)
    bool empty() const {
        return s.empty();
    }

    typename pbds_set::iterator begin() const { return s.begin(); }
    typename pbds_set::iterator end() const { return s.end(); }
    typename pbds_set::reverse_iterator rbegin() const { return s.rbegin(); }
    typename pbds_set::reverse_iterator rend() const { return s.rend(); }
};
