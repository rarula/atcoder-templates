#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
struct RankedMultiset {
private:
    using u64 = uint64_t;
    using K = pair<T, u64>;
    using pbds_multiset = tree<K, null_type, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
    pbds_multiset ms;
    u64 id; // 多重集合にするために、各要素に連番を付与するためのもの

public:
    RankedMultiset() : id(0) {}

    // x を挿入する
    // O(log n)
    void insert(const T& x) {
        ms.insert(make_pair(x, id));
        id++;
    }

    // x が存在するなら、そのうち1つだけ削除する
    // O(log n)
    void erase(const T& x) {
        auto it = ms.lower_bound(make_pair(x, 0));
        if (it != ms.end() && !(x < it->first)) ms.erase(it);
    }

    // k 番目 (0-indexed) に小さい値を返す
    // O(log n)
    T kth_smallest(int k) const {
        assert(0 <= k && k < size());
        return ms.find_by_order(k)->first;
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
        return ms.order_of_key(make_pair(x, 0));
    }

    // x 以下の値の個数を返す
    // O(log n)
    int count_less_equal(const T& x) const {
        return ms.order_of_key(make_pair(x, id));
    }

    // x の個数を返す
    // O(log n)
    int count(const T& x) const {
        return count_less_equal(x) - count_less(x);
    }

    // 要素数を返す
    // O(1)
    int size() const {
        return ms.size();
    }

    // 多重集合が空のとき true 、空でないとき false を返す
    // O(1)
    bool empty() const {
        return ms.empty();
    }

    typename pbds_multiset::iterator begin() const { return ms.begin(); }
    typename pbds_multiset::iterator end() const { return ms.end(); }
    typename pbds_multiset::reverse_iterator rbegin() const { return ms.rbegin(); }
    typename pbds_multiset::reverse_iterator rend() const { return ms.rend(); }
};
