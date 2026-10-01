#include <bits/stdc++.h>
using namespace std;
 
void transformArray(vector<int>& a) {
    int n = a.size();
    vector<int> v;
    v.reserve(n * (n - 1) / 2);
 
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            v.push_back(a[i] ^ a[j]);
        }
    }
 
    sort(v.begin(), v.end());
 
    for (int i = 0; i < n; i++) {
        a[i] = v[i];
    }
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
 
        for (int& x : a) {
            cin >> x;
        }
 
        sort(a.begin(), a.end());
 
        vector<int> ans;
        ans.push_back(a.back() - a.front());
 
        while (a.back() != 0) {
            transformArray(a);
            ans.push_back(a.back() - a.front());
        }
 
        while (q--) {
            int x;
            cin >> x;
 
            if (x >= (int)ans.size()) {
                cout << ans.back() << '
';
            } else {
                cout << ans[x] << '
';
            }
        }
    }
 
    return 0;
}