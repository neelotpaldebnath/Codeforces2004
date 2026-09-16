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
 
        // Necessary and sufficient condition
        if (k < n || k > 2 * n - 1) {
            cout << -1 << '
';
            continue;
        }
 
        vector<vector<int>> a(n, vector<int>(n, 0));
 
        int extra = k - n;       // Number of new column minima
        int usedCols = n - extra;
 
        // Put 1..n as row minima.
        // They occupy only the first 'usedCols' columns.
        for (int i = 0; i < n; i++) {
            int col = i % usedCols;
            a[i][col] = i + 1;
        }
 
        // Put n+1 ... n+extra as minima of the remaining columns.
        for (int j = 0; j < extra; j++) {
            int col = usedCols + j;
            a[0][col] = n + j + 1;
        }
 
        // Fill all remaining cells with the largest unused numbers.
        int cur = n + extra + 1;
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] == 0) {
                    a[i][j] = cur++;
                }
            }
        }
 
        // Output
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j] << (j + 1 == n ? '
' : ' ');
            }
        }
    }
 
    return 0;
}