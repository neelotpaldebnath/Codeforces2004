#include <bits/stdc++.h>
using namespace std;
 
int MOD;
 
long long mod_pow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}
 
void solve() {
    int n;
    cin >> n >> MOD;
 
    vector<long long> fact(2 * n + 1), invfact(2 * n + 1);
 
    fact[0] = 1;
    for (int i = 1; i <= 2 * n; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
 
    invfact[2 * n] = mod_pow(fact[2 * n], MOD - 2);
 
    for (int i = 2 * n; i >= 1; --i) {
        invfact[i - 1] = invfact[i] * i % MOD;
    }
 
    auto C = [&](int a, int b) -> long long {
        if (b < 0 || b > a) return 0;
        return fact[a] * invfact[b] % MOD * invfact[a - b] % MOD;
    };
 
    auto F = [&](int a, int b) -> long long {
        if (b < 0 || b > a) return 0;
        return fact[a] * invfact[b + 1] % MOD * invfact[a - b] % MOD;
    };
 
    vector<long long> cat2(n + 1);
 
    for (int i = 0; i <= n; ++i) {
        long long cat = F(2 * i, i);
        cat2[i] = cat * cat % MOD;
    }
 
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1));
 
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = cat2[j];
    }
 
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (dp[i - 1][j] == 0) continue;
 
            for (int k = 0; j + k <= n; ++k) {
                dp[i][j + k] += dp[i - 1][j] * cat2[k] % MOD;
 
                if (dp[i][j + k] >= MOD) {
                    dp[i][j + k] -= MOD;
                }
            }
        }
    }
 
    vector<long long> ans(n + 1);
 
    for (int i = 0; i <= n; ++i) {
        ans[i] = F(2 * n, i) * dp[i][n - i] % MOD;
    }
 
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j <= n; ++j) {
            ans[i] -= ans[j] * C(j, i) % MOD;
 
            if (ans[i] < 0) {
                ans[i] += MOD;
            }
        }
    }
 
    for (int i = 0; i <= n; ++i) {
        cout << ans[i] << (i == n ? '
' : ' ');
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        solve();
    }
 
    return 0;
}