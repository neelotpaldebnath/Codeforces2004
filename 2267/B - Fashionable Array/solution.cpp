#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        int n;
        cin >> n;
 
        vector<int> cnt(101);
 
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            cnt[x]++;
        }
 
        for (int k = 1; k <= n; k++) {
            for (int x = 100; x >= 1; x--) {
                if (cnt[x] >= k) {
                    cout << x << ' ';
                }
            }
        }
 
        cout << '
';
    }
 
    return 0;
}