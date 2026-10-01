#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T;
    cin >> T;
 
    while (T--) {
        int n, x;
        cin >> n >> x;
 
        vector<int> a(n);
        for (int &v : a)
            cin >> v;
 
        if (x == 1) {
            cout << 0 << '
';
            continue;
        }
 
        vector<int> primes;
        int temp = x;
 
        for (int p = 2; 1LL * p * p <= temp; p++) {
            if (temp % p == 0) {
                primes.push_back(p);
                while (temp % p == 0)
                    temp /= p;
            }
        }
 
        if (temp > 1)
            primes.push_back(temp);
 
        long long ans = 0;
 
        for (int p : primes) {
            long long sum = 0;
 
            for (int v : a) {
                if (v % p == 0)
                    sum += v;
            }
 
            ans = max(ans, sum);
        }
 
        cout << ans << '
';
    }
 
    return 0;
}