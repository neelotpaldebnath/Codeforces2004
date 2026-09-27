#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
const int MOD = 998244353;
const int G = 3;
const int MAXN = 200000;
const int B = 18;
 
int power(int a, int b) {
    int r = 1;
 
    while (b) {
        if (b & 1) r = (ll)r * a % MOD;
        a = (ll)a * a % MOD;
        b >>= 1;
    }
 
    return r;
}
 
struct NTT {
    int n;
    vector<int> rev, roots;
 
    NTT(int n) : n(n), rev(n), roots(n) {
        for (int i = 1; i < n; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
        }
 
        for (int len = 1; len < n; len <<= 1) {
            int w = power(G, (MOD - 1) / (len << 1));
            roots[len] = 1;
 
            for (int i = 1; i < len; i++) {
                roots[len + i] = (ll)roots[len + i - 1] * w % MOD;
            }
        }
    }
 
    void transform(vector<int>& a) {
        for (int i = 0; i < n; i++) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }
 
        for (int len = 1; len < n; len <<= 1) {
            for (int st = 0; st < n; st += len << 1) {
                for (int j = 0; j < len; j++) {
                    int x = a[st + j];
                    int y = (ll)a[st + j + len] * roots[len + j] % MOD;
 
                    a[st + j] = x + y;
                    if (a[st + j] >= MOD) a[st + j] -= MOD;
 
                    a[st + j + len] = x - y;
                    if (a[st + j + len] < 0) a[st + j + len] += MOD;
                }
            }
        }
    }
};
 
vector<int> fact(2 * MAXN + 1);
vector<int> invfact(2 * MAXN + 1);
vector<int> cat(MAXN + 1);
 
void init() {
    fact[0] = 1;
 
    for (int i = 1; i <= 2 * MAXN; i++) {
        fact[i] = (ll)fact[i - 1] * i % MOD;
    }
 
    invfact[2 * MAXN] = power(fact[2 * MAXN], MOD - 2);
 
    for (int i = 2 * MAXN; i >= 1; i--) {
        invfact[i - 1] = (ll)invfact[i] * i % MOD;
    }
 
    for (int i = 0; i <= MAXN; i++) {
        cat[i] = (ll)fact[2 * i] * invfact[i] % MOD;
        cat[i] = (ll)cat[i] * invfact[i + 1] % MOD;
    }
}
 
void solve() {
    int n;
    cin >> n;
 
    vector<int> a(n), pref(n + 1);
 
    for (int& x : a) {
        cin >> x;
    }
 
    if (n == 1) {
        cout << 0 << '
';
        return;
    }
 
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] ^ a[i - 1];
    }
 
    vector<int> weight(n);
    int W = 0;
 
    for (int d = 1; d < n; d++) {
        weight[d] = (ll)cat[d] * cat[n - d] % MOD;
        W = (W + (ll)(n - d + 1) * weight[d]) % MOD;
    }
 
    int len = 1;
 
    while (len < 2 * (n + 1)) {
        len <<= 1;
    }
 
    NTT ntt(len);
 
    vector<int> kernel(len);
 
    for (int d = 1; d < n; d++) {
        kernel[d] = weight[d];
        kernel[len - d] = weight[d];
    }
 
    ntt.transform(kernel);
 
    int answer = (ll)((1 << B) - 1) * W % MOD;
    int invLen = power(len, MOD - 2);
    int inv2 = (MOD + 1) / 2;
 
    int totalXor = pref[n];
 
    vector<int> seq(len);
 
    for (int b = 0; b < B; b++) {
        if ((totalXor >> b) & 1) {
            continue;
        }
 
        fill(seq.begin(), seq.end(), 0);
 
        for (int i = 0; i <= n; i++) {
            seq[i] = ((pref[i] >> b) & 1) ? MOD - 1 : 1;
        }
 
        ntt.transform(seq);
 
        int sum = 0;
 
        for (int k = 0; k < len; k++) {
            int opposite = (len - k) & (len - 1);
 
            int cur = (ll)kernel[k] * seq[k] % MOD;
            cur = (ll)cur * seq[opposite] % MOD;
 
            sum += cur;
 
            if (sum >= MOD) {
                sum -= MOD;
            }
        }
 
        int r = (ll)sum * invLen % MOD;
        r = (ll)r * inv2 % MOD;
 
        answer -= (ll)(1 << b) * r % MOD;
 
        if (answer < 0) {
            answer += MOD;
        }
    }
 
    cout << answer << '
';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    init();
 
    int t;
    cin >> t;
 
    while (t--) {
        solve();
    }
 
    return 0;
}