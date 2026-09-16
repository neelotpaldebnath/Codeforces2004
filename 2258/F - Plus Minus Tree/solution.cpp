#include <bits/stdc++.h>
using namespace std;
 
struct SegTree {
    int n;
    vector<int> mx, lazy, mn, mnLazy;
 
    SegTree(int n) : n(n) {
        mx.assign(4 * n + 5, -1000000000);
        lazy.assign(4 * n + 5, 0);
        mn.assign(4 * n + 5, 1000000000);
        mnLazy.assign(4 * n + 5, 0);
    }
 
    void build(int p, int l, int r, const vector<int>& score,
               const vector<int>& need) {
        if (l == r) {
            mx[p] = score[l];
            mn[p] = need[l];
            return;
        }
 
        int m = (l + r) >> 1;
 
        build(p << 1, l, m, score, need);
        build(p << 1 | 1, m + 1, r, score, need);
 
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
        mn[p] = min(mn[p << 1], mn[p << 1 | 1]);
    }
 
    void push(int p) {
        if (lazy[p]) {
            int x = lazy[p];
 
            mx[p << 1] += x;
            lazy[p << 1] += x;
 
            mx[p << 1 | 1] += x;
            lazy[p << 1 | 1] += x;
 
            lazy[p] = 0;
        }
 
        if (mnLazy[p]) {
            int x = mnLazy[p];
 
            mn[p << 1] += x;
            mnLazy[p << 1] += x;
 
            mn[p << 1 | 1] += x;
            mnLazy[p << 1 | 1] += x;
 
            mnLazy[p] = 0;
        }
    }
 
    void addScore(int p, int l, int r, int ql, int qr, int x) {
        if (ql <= l && r <= qr) {
            mx[p] += x;
            lazy[p] += x;
            return;
        }
 
        push(p);
 
        int m = (l + r) >> 1;
 
        if (ql <= m)
            addScore(p << 1, l, m, ql, qr, x);
 
        if (qr > m)
            addScore(p << 1 | 1, m + 1, r, ql, qr, x);
 
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }
 
    void addNeed(int p, int l, int r, int ql, int qr, int x) {
        if (ql <= l && r <= qr) {
            mn[p] += x;
            mnLazy[p] += x;
            return;
        }
 
        push(p);
 
        int m = (l + r) >> 1;
 
        if (ql <= m)
            addNeed(p << 1, l, m, ql, qr, x);
 
        if (qr > m)
            addNeed(p << 1 | 1, m + 1, r, ql, qr, x);
 
        mn[p] = min(mn[p << 1], mn[p << 1 | 1]);
    }
 
    void removePoint(int p, int l, int r, int idx) {
        if (l == r) {
            mx[p] = -1000000000;
            return;
        }
 
        push(p);
 
        int m = (l + r) >> 1;
 
        if (idx <= m)
            removePoint(p << 1, l, m, idx);
        else
            removePoint(p << 1 | 1, m + 1, r, idx);
 
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }
 
    int firstZero(int p, int l, int r, int ql, int qr) {
        if (r < ql || qr < l || mn[p] > 0)
            return -1;
 
        if (l == r)
            return l;
 
        push(p);
 
        int m = (l + r) >> 1;
 
        int res = firstZero(p << 1, l, m, ql, qr);
 
        if (res != -1)
            return res;
 
        return firstZero(p << 1 | 1, m + 1, r, ql, qr);
    }
 
    void setNeed(int p, int l, int r, int idx, int value) {
        if (l == r) {
            mn[p] = value;
            mnLazy[p] = 0;
            return;
        }
 
        push(p);
 
        int m = (l + r) >> 1;
 
        if (idx <= m)
            setNeed(p << 1, l, m, idx, value);
        else
            setNeed(p << 1 | 1, m + 1, r, idx, value);
 
        mn[p] = min(mn[p << 1], mn[p << 1 | 1]);
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T;
    cin >> T;
 
    while (T--) {
        int n;
        cin >> n;
 
        vector<int> a(n);
        for (int &x : a)
            cin >> x;
 
        vector<vector<int>> g(n);
 
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
 
        vector<int> parent(n, -1), order;
        order.reserve(n);
 
        parent[0] = 0;
        order.push_back(0);
 
        for (int i = 0; i < (int)order.size(); ++i) {
            int v = order[i];
 
            for (int u : g[v]) {
                if (u == parent[v])
                    continue;
 
                parent[u] = v;
                order.push_back(u);
            }
        }
 
        vector<int> val = a;
 
        for (int &x : val)
            if (x == 0)
                x = 1;
 
        vector<int> sub(n), sz(n, 1), heavy(n, -1);
 
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            sub[v] += val[v];
 
            int best = 0;
 
            for (int u : g[v]) {
                if (parent[u] != v)
                    continue;
 
                sub[v] += sub[u];
                sz[v] += sz[u];
 
                if (sz[u] > best) {
                    best = sz[u];
                    heavy[v] = u;
                }
            }
        }
 
        vector<int> head(n), pos(n), rev(n);
 
        int timer = 0;
 
        vector<pair<int,int>> st;
        st.push_back({0, 0});
 
        while (!st.empty()) {
            auto [h, v] = st.back();
            st.pop_back();
 
            while (v != -1) {
                head[v] = h;
                pos[v] = timer;
                rev[timer] = v;
                ++timer;
 
                for (int u : g[v]) {
                    if (parent[u] == v && u != heavy[v])
                        st.push_back({u, u});
                }
 
                v = heavy[v];
            }
        }
 
        auto sgn = [&](int x) {
            if (x > 1) return 1;
            if (x < 1) return -1;
            return 0;
        };
 
        vector<int> score(n);
        score[0] = sgn(sub[0]);
 
        for (int i = 1; i < n; ++i) {
            int v = order[i];
            score[v] = score[parent[v]] + sgn(sub[v]);
        }
 
        vector<int> scorePos(n);
        vector<int> need(n, 1000000000);
        vector<int> state(n, 0);
 
        vector<int> zeroSub(n);
 
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
 
            zeroSub[v] += (a[v] == 0);
 
            for (int u : g[v]) {
                if (parent[u] == v)
                    zeroSub[v] += zeroSub[u];
            }
        }
 
        for (int i = 0; i < n; ++i) {
            int v = rev[i];
 
            scorePos[i] = (a[v] == 0 ? score[v] : -1000000000);
 
            if (zeroSub[v] == 0 || sub[v] <= 0)
                continue;
 
            if (sub[v] == 1) {
                need[i] = 1;
                state[v] = 1;
            } else if (sub[v] & 1) {
                need[i] = (sub[v] - 1) / 2;
                state[v] = 2;
            } else {
                need[i] = sub[v] / 2;
                state[v] = 3;
            }
        }
 
        SegTree seg(n);
        seg.build(1, 0, n - 1, scorePos, need);
 
        long long answer = 0;
 
        for (int x : sub)
            answer += abs(x);
 
        while (seg.mx[1] > 0) {
            int bestScore = seg.mx[1];
 
            int p = -1;
 
            function<int(int,int,int)> getIndex =
                [&](int node, int l, int r) -> int {
                    if (l == r)
                        return l;
 
                    seg.push(node);
 
                    int m = (l + r) >> 1;
 
                    if (seg.mx[node << 1] == seg.mx[1])
                        return getIndex(node << 1, l, m);
 
                    return getIndex(node << 1 | 1, m + 1, r);
                };
 
            p = getIndex(1, 0, n - 1);
 
            int z = rev[p];
 
            seg.removePoint(1, 0, n - 1, p);
 
            answer -= 2LL * bestScore;
 
            vector<pair<int,int>> ranges;
 
            int v = z;
 
            while (head[v] != 0) {
                ranges.push_back({pos[head[v]], pos[v]});
                v = parent[head[v]];
            }
 
            ranges.push_back({0, pos[v]});
 
            for (auto [l, r] : ranges)
                seg.addNeed(1, 0, n - 1, l, r, -1);
 
            for (auto [l, r] : ranges) {
                while (true) {
                    int q = seg.firstZero(1, 0, n - 1, l, r);
 
                    if (q == -1)
                        break;
 
                    int u = rev[q];
                    int delta;
 
                    if (state[u] == 2) {
                        delta = -1;
                        state[u] = 1;
                        seg.setNeed(1, 0, n - 1, q, 1);
                    } else if (state[u] == 1) {
                        delta = -1;
                        state[u] = 0;
                        seg.setNeed(1, 0, n - 1, q, 1000000000);
                    } else {
                        delta = -2;
                        state[u] = 0;
                        seg.setNeed(1, 0, n - 1, q, 1000000000);
                    }
 
                    seg.addScore(
                        1, 0, n - 1,
                        pos[u],
                        pos[u] + sz[u] - 1,
                        delta
                    );
                }
            }
        }
 
        cout << answer << '
';
    }
 
    return 0;
}