#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
template<typename T = ll>
struct CoordinateCompression {
private:
    bool built;
    vector<T> xs;

public:
    CoordinateCompression() : built(false) {}

    // 圧縮対象に値 x を追加する
    // 償却 O(1)
    void add(T x) {
        xs.push_back(x);
        built = false;
    }

    // 座標圧縮する
    // O(n log n)
    void build() {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        built = true;
    }

    // 登録済みの値 x の圧縮後のインデックスを返す
    // O(log n)
    int index(T x) const {
        assert(built);
        int i = std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        assert(i < size()); // 未登録の値を取得しようとしたときエラー
        assert(xs[i] == x); // 未登録の値を取得しようとしたときエラー
        return i;
    }

    // 登録済みの値のうち x 以上で最小のものについて、圧縮後のインデックスを返す。そのような値が存在しないなら size() を返す
    // O(log n)
    int lower_bound(T x) const {
        assert(built);
        return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }

    // 登録済みの値のうち x より大きい最小のものについて、圧縮後のインデックスを返す。そのような値が存在しないなら size() を返す
    // O(log n)
    int upper_bound(T x) const {
        assert(built);
        return std::upper_bound(xs.begin(), xs.end(), x) - xs.begin();
    }

    // 圧縮後のインデックス i に対応する元の値を返す
    // O(1)
    T value(int i) const {
        assert(built);
        assert(0 <= i && i < size());
        return xs[i];
    }

    // 登録済みの値から重複を除いて昇順に並べたリストを返す
    // O(n)
    vector<T> values() const {
        assert(built);
        return xs;
    }

    // 値 x が登録されているなら true 、登録されていないなら false を返す
    // O(log n)
    bool contains(T x) const {
        assert(built);
        int i = lower_bound(x);
        return i < size() && xs[i] == x;
    }

    // 圧縮後のインデックスの数を返す
    // O(1)
    int size() const {
        assert(built);
        return xs.size();
    }

    // 値が何も追加されていないとき true 、1つでも追加されているなら false を返す
    // O(1)
    bool empty() const {
        return xs.empty();
    }
};
