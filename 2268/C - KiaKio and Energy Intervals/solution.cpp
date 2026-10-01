#include <bits/stdc++.h>
using namespace std;
 
const int N = 200005;
const int LG = 18;
 
int t, n;
int a[N];
int par[LG][N];
int pref[N];
int cnt[N * 2];
int answ = 0;
int maxi = 0;
 
int getmx(int l, int r) {
    int res = l;
 
    for (int i = LG - 1; i >= 0; i--) {
        if (l + (1 << i) - 1 <= r) {
            int x = par[i][l];
 
            if (a[x] > a[res])
                res = x;
 
            l += 1 << i;
        }
    }
 
    return res;
}
 
void divide(int l, int r) {
    if (l > r)
        return;
 
    if (l == r) {
        cnt[pref[l]]++;
        return;
    }
 
    if (l == r - 1) {
        cnt[pref[l]]++;
        cnt[pref[r]]++;
 
        if ((max(a[l], a[r]) & answ) == answ)
            maxi = max(maxi, pref[l - 1] ^ pref[r]);
 
        return;
    }
 
    int mid = getmx(l, r);
 
    if (r - mid > mid - l) {
        divide(l, mid - 1);
 
        for (int i = l; i < mid; i++)
            cnt[pref[i]]--;
 
        divide(mid + 1, r);
 
        for (int i = mid - 1; i >= l - 1; i--) {
            if (cnt[answ ^ pref[i]] > 0 &&
                (a[mid] & answ) == answ) {
                maxi = answ;
            }
 
            if (i == mid - 1)
                cnt[pref[mid]]++;
        }
 
        for (int i = mid - 1; i >= l; i--)
            cnt[pref[i]]++;
    } else {
        divide(mid + 1, r);
 
        for (int i = mid + 1; i <= r; i++)
            cnt[pref[i]]--;
 
        divide(l, mid - 1);
 
        cnt[pref[mid - 1]]--;
        cnt[pref[l - 1]]++;
 
        for (int i = mid; i <= r; i++) {
            if (cnt[answ ^ pref[i]] > 0 &&
                (a[mid] & answ) == answ) {
                maxi = answ;
            }
 
            if (i == mid)
                cnt[pref[mid - 1]]++;
        }
 
        cnt[pref[l - 1]]--;
 
        for (int i = mid; i <= r; i++)
            cnt[pref[i]]++;
    }
}
 
bool check() {
    maxi = 0;
 
    for (int i = 1; i <= n; i++)
        pref[i] = pref[i - 1] ^ (a[i] & answ);
 
    divide(1, n);
 
    for (int i = 1; i <= n; i++)
        cnt[pref[i]] = 0;
 
    return maxi == answ;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> t;
 
    while (t--) {
        cin >> n;
 
        int mx = 0;
        int direct = 0;
 
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
            par[0][i] = i;
        }
 
        for (int i = 1; i <= n; i++)
            direct ^= a[i] & mx;
 
        for (int i = n; i >= 1; i--) {
            for (int j = 1; j < LG; j++) {
                int x = par[j - 1][i];
                int y = par[j - 1][min(n, i + (1 << (j - 1)))];
 
                if (a[x] > a[y])
                    par[j][i] = x;
                else
                    par[j][i] = y;
            }
        }
 
        answ = 0;
 
        for (int bit = LG - 1; bit >= 0; bit--) {
            answ |= 1 << bit;
 
            if (!check())
                answ ^= 1 << bit;
        }
 
        cout << max(answ, direct) << '
';
 
        for (int i = 1; i <= n; i++) {
            a[i] = 0;
            pref[i] = 0;
        }
    }
 
    return 0;
}