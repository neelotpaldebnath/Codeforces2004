#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
void solve() {
    int n, m;
    cin >> n >> m;
 
    vector<int> freq(m + 1, 0);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        freq[a]++;
    }
 
    // Prefix sum of frequencies: pref[i] = sum(freq[1...i])
    vector<int> pref(m + 1, 0);
    for (int i = 1; i <= m; ++i) {
        pref[i] = pref[i - 1] + freq[i];
    }
 
    int max_carrots = 0;
 
    // Try all possible target carrot lengths x
    for (int x = 1; x <= m; ++x) {
        // Count of carrots with initial size >= x
        int count_ge_x = pref[m] - pref[x - 1];
 
        // Carrots of size exactly 2*x yield 2 pieces instead of 1
        int count_2x = (2 * x <= m) ? freq[2 * x] : 0;
 
        int total_pieces_of_x = count_ge_x + count_2x;
        max_carrots = max(max_carrots, total_pieces_of_x);
    }
 
    cout << max_carrots << "
";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
 
    return 0;
}