#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Trie {
private:
    struct Node {
        int pass_count = 0;  // この頂点を通る文字列の個数
        int end_count = 0;   // この頂点で終わる文字列の個数
        map<char, int> next; // 次の文字を key, 次の文字の頂点番号を value とした連想配列
    };
    vector<Node> nodes;

    // str を辿った先の頂点番号を返す
    // 存在しなければ -1 を返す
    // O(|str|)
    int find_node(const string& str) const {
        int v = 0;
        for (char c : str) {
            auto it = nodes[v].next.find(c);
            if (it == nodes[v].next.end()) return -1;
            v = it->second;
        }
        return v;
    }

public:
    Trie() : nodes(1) {}

    // 文字列を1つ追加する
    // O(|str|)
    void insert(const string& str) {
        int v = 0;
        for (char c : str) {
            nodes[v].pass_count++;
            auto it = nodes[v].next.find(c);
            if (it == nodes[v].next.end()) {
                int nv = nodes.size();
                nodes[v].next[c] = nv;
                nodes.push_back(Node());
                v = nv;
            }
            else v = it->second;
        }
        nodes[v].pass_count++;
        nodes[v].end_count++;
    }

    // 文字列を1つ削除する。 str が存在しなければ何もしない。
    // 削除できたら true、できなければ false を返す
    // O(|str|)
    bool erase(const string& str) {
        int v = find_node(str);
        if (v == -1) return false;
        if (nodes[v].end_count == 0) return false;
        v = 0;
        for (char c : str) {
            nodes[v].pass_count--;
            v = nodes[v].next[c];
        }
        nodes[v].pass_count--;
        nodes[v].end_count--;
        return true;
    }

    // str を接頭辞に持つ文字列をすべて削除する
    // 削除した文字列の個数を返す
    // O(|str|)
    int erase_prefix(const string& str) {
        int v = find_node(str);
        if (v == -1) return 0;
        if (nodes[v].pass_count == 0) return 0;
        int remove_count = nodes[v].pass_count;
        v = 0;
        for (char c : str) {
            nodes[v].pass_count -= remove_count;
            v = nodes[v].next[c];
        }
        // str 以下の部分木を論理削除する (頂点自体は残るが、そこへ向かう辺をすべて切る)
        nodes[v].pass_count -= remove_count;
        nodes[v].end_count = 0;
        nodes[v].next.clear();
        return remove_count;
    }

    // 追加されている文字列のうち str そのものの個数を返す
    // O(|str|)
    int count_string(const string& str) const {
        int v = find_node(str);
        if (v == -1) return 0;
        return nodes[v].end_count;
    }

    // 追加されている文字列のうち str を接頭辞に持つ文字列の個数を返す
    // O(|str|)
    int count_prefix(const string& str) const {
        int v = find_node(str);
        if (v == -1) return 0;
        return nodes[v].pass_count;
    };

    // 追加されている文字列のうち str の接頭辞となる文字列が存在するとき true、存在しないとき false を返す
    // O(|str|)
    bool has_prefix_of(const string& str) const {
        int v = 0;
        for (char c : str) {
            if (nodes[v].end_count > 0) return true;
            auto it = nodes[v].next.find(c);
            if (it == nodes[v].next.end()) return false;
            v = it->second;
        }
        return nodes[v].end_count > 0;
    }

    // 追加されている文字列の総数を返す。同じ文字列を複数回 insert した場合もそれぞれ数える。
    // O(1)
    int size() const {
        return nodes[0].pass_count;
    }

    // Trie が空のとき true、空でないとき false を返す
    // O(1)
    bool empty() const {
        return size() == 0;
    }
};
