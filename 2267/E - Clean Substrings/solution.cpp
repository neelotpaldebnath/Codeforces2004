#include <bits/stdc++.h>
using namespace std;
 
struct Node {
    long long c0 = 1, c1 = 0;
    int xr = 0;
};
 
Node mergeNode(const Node& a, const Node& b) {
    Node res;
    res.xr = a.xr ^ b.xr;
    res.c0 = a.c0;
    res.c1 = a.c1;
 
    if (a.xr == 0) {
        res.c0 += b.c0 - 1;
        res.c1 += b.c1;
    } else {
        res.c0 += b.c1;
        res.c1 += b.c0 - 1;
    }
 
    return res;
}
 
struct SegTree {
    int size;
    vector<Node> tree;
 
    SegTree(const vector<int>& a) {
        int n = (int)a.size();
        size = 1;
        while (size < n) size <<= 1;
 
        tree.assign(2 * size, Node());
 
        for (int i = 0; i < n; i++) {
            if (a[i] == 0) {
                tree[size + i] = {2, 0, 0};
            } else {
                tree[size + i] = {1, 1, 1};
            }
        }
 
        for (int i = size - 1; i >= 1; i--) {
            tree[i] = mergeNode(tree[i << 1], tree[i << 1 | 1]);
        }
    }
 
    void flip(int pos) {
        int p = size + pos;
 
        if (tree[p].xr == 0)
            tree[p] = {1, 1, 1};
        else
            tree[p] = {2, 0, 0};
 
        p >>= 1;
 
        while (p) {
            tree[p] = mergeNode(tree[p << 1], tree[p << 1 | 1]);
            p >>= 1;
        }
    }
 
    Node root() {
        return tree[1];
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T;
    cin >> T;
 
    while (T--) {
        int n, q;
        cin >> n >> q;
 
        string s;
        cin >> s;
 
        if (n == 1) {
            cout << 0;
            while (q--) {
                int x;
                cin >> x;
                cout << ' ' << 0;
            }
            cout << '
';
            continue;
        }
 
        vector<int> a(n - 1);
 
        long long W = 0;
 
        for (int i = 0; i < n - 1; i++) {
            a[i] = (s[i] != s[i + 1]);
 
            if (a[i]) {
                long long pos = i + 1;
                W += pos * (n - pos);
            }
        }
 
        SegTree st(a);
 
        auto getAnswer = [&]() -> long long {
            Node r = st.root();
            long long odd = r.c0 * r.c1;
            return (W + odd) / 2;
        };
 
        cout << getAnswer();
 
        while (q--) {
            int x;
            cin >> x;
            --x;
 
            s[x] = (s[x] == '0' ? '1' : '0');
 
            if (x > 0) {
                int j = x - 1;
 
                long long weight = 1LL * (j + 1) * (n - (j + 1));
 
                if (a[j])
                    W -= weight;
                else
                    W += weight;
 
                a[j] ^= 1;
                st.flip(j);
            }
 
            if (x + 1 < n) {
                int j = x;
 
                long long weight = 1LL * (j + 1) * (n - (j + 1));
 
                if (a[j])
                    W -= weight;
                else
                    W += weight;
 
                a[j] ^= 1;
                st.flip(j);
            }
 
            cout << ' ' << getAnswer();
        }
 
        cout << '
';
    }
 
    return 0;
}