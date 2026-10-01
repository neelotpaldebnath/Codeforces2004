#include <bits/stdc++.h>
using namespace std;
 
bool good(int x) {
    return __builtin_popcount(x) % 2 == 0;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        int n, q;
        cin >> n >> q;
 
        vector<int> a(n);
        int ans = 0;
 
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            ans += good(a[i]);
        }
 
        cout << ans;
 
        while (q--) {
            int p, x;
            cin >> p >> x;
            --p;
 
            ans -= good(a[p]);
            a[p] = x;
            ans += good(a[p]);
 
            cout << ' ' << ans;
        }
 
        cout << '
';
    }
 
    return 0;
}