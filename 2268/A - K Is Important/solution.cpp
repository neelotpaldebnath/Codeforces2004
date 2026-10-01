#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        int n, k;
        cin >> n >> k;
 
        vector<long long> a(n + 1);
 
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
 
        long long ans = 0;
        vector<long long> v;
 
        for (int i = 1; i <= n; i++) {
            if (i >= k && i <= n - k + 1) {
                ans += a[i];
            } else {
                v.push_back(a[i]);
            }
        }
 
        int need = max(0, (int)v.size() - (k - 1));
 
        int l = 0;
        int r = (int)v.size() - 1;
 
        while (need--) {
            ans += max(v[l], v[r]);
            l++;
            r--;
        }
 
        cout << ans << '
';
    }
 
    return 0;
}