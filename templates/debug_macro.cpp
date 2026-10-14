#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace dbg {
    template<class T> struct type { static constexpr int id = 0; };

    // C-style array, array, vector, set, multiset
    template<class T, size_t N> struct type<T[N]> { static constexpr int id = 10; };
    template<class T, size_t N> struct type<array<T,N>> { static constexpr int id = 10; };
    template<class T, class A> struct type<vector<T,A>> { static constexpr int id = 10; };
    template<class T, class C, class A> struct type<set<T,C,A>> { static constexpr int id = 11; };
    template<class T, class C, class A> struct type<multiset<T,C,A>> { static constexpr int id = 11; };

    // map, unordered_map
    template<class K, class V, class C, class A> struct type<map<K,V,C,A>> { static constexpr int id = 20; };
    template<class K, class V, class H, class E, class A> struct type<unordered_map<K,V,H,E,A>> { static constexpr int id = 20; };

    // queue, stack, priority_queue, deque
    template<class T, class C> struct type<queue<T,C>> { static constexpr int id = 30; };
    template<class T, class C> struct type<stack<T,C>> { static constexpr int id = 31; };
    template<class T, class C, class P> struct type<priority_queue<T,C,P>> { static constexpr int id = 31; };
    template<class T, class A> struct type<deque<T,A>> { static constexpr int id = 32; };

    // pair, tuple
    template<class T, class U> struct type<pair<T,U>> { static constexpr int id = 40; };
    template<class... T> struct type<tuple<T...>> { static constexpr int id = 41; };

    template<class T>
    void print(const T& x) {
        using U = remove_cv_t<remove_reference_t<T>>;

        if constexpr (is_array_v<U> && is_same_v<remove_cv_t<remove_extent_t<U>>, char>) {
            constexpr size_t N = extent_v<U>;
            cerr.write(x, N - (x[N - 1] == '\n'));
        }
        else if constexpr (type<U>::id == 0) {
            if constexpr (is_same_v<U, bool>)
                cerr << boolalpha << x << noboolalpha;
            else
                cerr << x;
        }
        else if constexpr (type<U>::id == 10 || type<U>::id == 11) {
            cerr << (type<U>::id == 10 ? "[ " : "{ ");
            bool first = true;
            for (const auto& v : x) {
                if (!first) cerr << ", ";
                first = false;
                print(v);
            }
            cerr << (type<U>::id == 10 ? " ]" : " }");
        }
        else if constexpr (type<U>::id == 20) {
            cerr << "{ ";
            bool first = true;
            for (const auto& [k, v] : x) {
                if (!first) cerr << ", ";
                first = false;
                print(k);
                cerr << ": ";
                print(v);
            }
            cerr << " }";
        }
        else if constexpr (type<U>::id == 30) {
            auto y = x;
            cerr << "front [ ";
            bool first = true;
            while (!y.empty()) {
                if (!first) cerr << ", ";
                first = false;
                print(y.front());
                y.pop();
            }
            cerr << " ]";
        }
        else if constexpr (type<U>::id == 31) {
            auto y = x;
            cerr << "top [ ";
            bool first = true;
            while (!y.empty()) {
                if (!first) cerr << ", ";
                first = false;
                print(y.top());
                y.pop();
            }
            cerr << " ]";
        }
        else if constexpr (type<U>::id == 32) {
            cerr << "front [ ";
            bool first = true;
            for (const auto& v : x) {
                if (!first) cerr << ", ";
                first = false;
                print(v);
            }
            cerr << " ] back";
        }
        else if constexpr (type<U>::id == 40) {
            cerr << "( ";
            print(x.first);
            cerr << ", ";
            print(x.second);
            cerr << " )";
        }
        else if constexpr (type<U>::id == 41) {
            cerr << "( ";
            bool first = true;
            apply([&](const auto&... values) {
                auto print_one = [&](const auto& value) {
                    if (!first) cerr << ", ";
                    first = false;
                    print(value);
                };
                (print_one(values), ...);
            }, x);
            cerr << " )";
        }
    }

    template<class... T>
    void debug(const T&... x) {
        bool first = true;
        auto print_one = [&](const auto& value) {
            if (!first) cerr << " | ";
            first = false;
            print(value);
        };
        (print_one(x), ...);
        cerr << '\n';
    }
}
#define DEBUG(...) dbg::debug(__VA_ARGS__)
#define DEBUG_VAR(x) cerr << #x << " = ", dbg::debug(x)
