#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// from https://github.com/rarula/atcoder-templates
template<typename T>
struct WaveletMatrix {
private:
    static_assert(is_integral_v<T>);
    static_assert(is_signed_v<T>);

    int H; // binary trie height
    int N; // length of integer sequence
    vector<vector<int>> data; // prefix sum of direction

    // 高さ h の区間 [l, r) において、その部分木の区間 [l0, r0), [l1, r1) を返す
    tuple<int,int,int,int> get_subtree_ranges(int h, int l, int r) {
        int l0 = l - data[h][l];
        int r0 = r - data[h][r];
        int l1 = data[h][l];
        int r1 = data[h][r];
        int mid = N - data[h][N];
        return {l0, r0, mid + l1, mid + r1};
    }

    T kth_smallest_rec(int h, int l, int r, int k) {
        if (h < 0) return 0;
        auto [l0, r0, l1, r1] = get_subtree_ranges(h, l, r);
        int left_size = r0 - l0;
        if (k < left_size) {
            return kth_smallest_rec(h-1, l0, r0, k);
        }
        else {
            return (T(1) << h) + kth_smallest_rec(h-1, l1, r1, k - left_size);
        }
    }

    int freq_less_rec(int h, int l, int r, T upper) {
        if (h < 0) return 0;
        auto [l0, r0, l1, r1] = get_subtree_ranges(h, l, r);
        int left_size = r0 - l0;
        if ((upper >> h) & 1) {
            return left_size + freq_less_rec(h-1, l1, r1, upper);
        } else {
            return freq_less_rec(h-1, l0, r0, upper);
        }
    }

public:
    // ビット幅を H として、ウェーブレット行列を配列 seq から構築する
    // O(|seq| * H)
    WaveletMatrix(int H, vector<T> seq) : H(H), N(seq.size()), data(H) {
        assert(0 <= H && H < numeric_limits<T>::digits);
        for (int i = 0; i < N; i++) assert(0 <= seq[i] && seq[i] < (T(1) << H));

        for (int h = H-1; h >= 0; h--) {
            vector<int> dir(N);
            vector<T> l, r;
            for (int i = 0; i < N; i++) {
                dir[i] = (seq[i] >> h) & 1;
                if (dir[i] == 0) {
                    l.push_back(seq[i]);
                } else {
                    r.push_back(seq[i]);
                }
            }
            int l_size = l.size();
            int r_size = r.size();
            for (int i = 0; i < l_size; i++) seq[i] = l[i];
            for (int i = 0; i < r_size; i++) seq[i + l_size] = r[i];

            data[h].resize(N+1);
            for (int i = 0; i < N; i++) data[h][i+1] = data[h][i] + dir[i];
        }
    }

    // 区間 [l, r) の中で k 番目 (0-indexed) に小さい値を返す
    // O(H)
    T kth_smallest(int l, int r, int k) {
        assert(0 <= l && l < r && r <= N);
        assert(0 <= k && k < r - l);
        return kth_smallest_rec(H-1, l, r, k);
    }

    // 区間 [l, r) の中で k 番目 (0-indexed) に大きい値を返す
    // O(H)
    T kth_largest(int l, int r, int k) {
        assert(0 <= l && l < r && r <= N);
        assert(0 <= k && k < r - l);
        return kth_smallest(l, r, r - l - k - 1);
    }

    // 区間 [l, r) の中で upper 未満の値の個数を返す
    // O(H)
    int freq(int l, int r, T upper) {
        assert(0 <= l && l <= r && r <= N);
        assert(0 <= upper && upper <= (T(1) << H));
        if (upper == (T(1) << H)) return r - l;
        return freq_less_rec(H-1, l, r, upper);
    }

    // 区間 [l, r) の中で lower 以上 upper 未満の値の個数を返す
    // O(H)
    int freq(int l, int r, T lower, T upper) {
        assert(0 <= l && l <= r && r <= N);
        assert(0 <= lower && lower <= upper && upper <= (T(1) << H));
        return freq(l, r, upper) - freq(l, r, lower);
    }
};
