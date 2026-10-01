#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        int n;
        char c;
        cin >> n >> c;
 
        string s;
        cin >> s;
 
        int ans = 0;
 
        for (int i = 0; i < n / 2; i++) {
            char left = s[i];
            char right = s[n - i - 1];
 
            if (left == right) {
                continue;
            }
 
            if (left == c || right == c) {
                ans += 1;
            } else {
                ans += 2;
            }
        }
 
        cout << ans << '
';
    }
 
    return 0;
}