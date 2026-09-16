#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
const long long INF = 4e18;
 
int n, q, x;
int SIZE;
vector<long long> tree;
vector<long long> d_arr;
vector<long long> s_arr;
 
// Min-plus matrix multiplication
void multiply(const long long* A, const long long* B, long long* C) {
    for (int i = 0; i < x * x; ++i) C[i] = INF;
    for (int i = 0; i < x; ++i) {
        for (int k = 0; k < x; ++k) {
            long long val1 = A[i * x + k];
            if (val1 == INF) continue;
            for (int j = 0; j < x; ++j) {
                long long val2 = B[k * x + j];
                if (val2 != INF) {
                    long long sum = val1 + val2;
                    if (sum < C[i * x + j]) {
                        C[i * x + j] = sum;
                    }
                }
            }
        }
    }
}
 
void copy_mat(const long long* src, long long* dst) {
    memcpy(dst, src, x * x * sizeof(long long));
}
 
// Generate the leaf matrix on the fly to save memory
void get_leaf(int idx, long long* mat) {
    if (idx >= n) { // Identity matrix for out-of-bounds nodes
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < x; ++j) {
                mat[i * x + j] = (i == j) ? 0 : INF;
            }
        }
        return;
    }
    long long L = d_arr[idx];
    long long cost = s_arr[idx];
    for (int u = 0; u < x; ++u) {
        for (int v = 0; v < x; ++v) {
            long long D = L - (v + 1) + (u + 1);
            if (D < 0) {
                mat[u * x + v] = INF;
            } else if (D == 0) {
                mat[u * x + v] = 0;
            } else {
                mat[u * x + v] = ((D - 1) / x) * cost;
            }
        }
    }
}
 
void build() {
    long long L[100], R[100];
    for (int i = SIZE - 1; i > 0; --i) {
        if (2 * i >= SIZE) get_leaf(2 * i - SIZE, L);
        else copy_mat(&tree[(2 * i) * x * x], L);
        
        if (2 * i + 1 >= SIZE) get_leaf(2 * i + 1 - SIZE, R);
        else copy_mat(&tree[(2 * i + 1) * x * x], R);
        
        multiply(L, R, &tree[i * x * x]);
    }
}
 
void update(int p) {
    p += SIZE;
    p /= 2;
    long long L[100], R[100];
    while (p > 0) {
        if (2 * p >= SIZE) get_leaf(2 * p - SIZE, L);
        else copy_mat(&tree[(2 * p) * x * x], L);
        
        if (2 * p + 1 >= SIZE) get_leaf(2 * p + 1 - SIZE, R);
        else copy_mat(&tree[(2 * p + 1) * x * x], R);
        
        multiply(L, R, &tree[p * x * x]);
        p /= 2;
    }
}
 
void query_range(int l, int r, long long* res) {
    if (l > r) { // Return identity
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < x; ++j) {
                res[i * x + j] = (i == j) ? 0 : INF;
            }
        }
        return;
    }
    long long resL[100], resR[100], node[100], tmp[100];
    bool hasL = false, hasR = false;
    l += SIZE;
    r += SIZE;
    
    while (l <= r) {
        if (l % 2 == 1) {
            if (l >= SIZE) get_leaf(l - SIZE, node);
            else copy_mat(&tree[l * x * x], node);
            
            if (!hasL) { copy_mat(node, resL); hasL = true; }
            else {
                multiply(resL, node, tmp);
                copy_mat(tmp, resL);
            }
            l++;
        }
        if (r % 2 == 0) {
            if (r >= SIZE) get_leaf(r - SIZE, node);
            else copy_mat(&tree[r * x * x], node);
            
            if (!hasR) { copy_mat(node, resR); hasR = true; }
            else {
                multiply(node, resR, tmp);
                copy_mat(tmp, resR);
            }
            r--;
        }
        l /= 2; r /= 2;
    }
    
    if (hasL && hasR) multiply(resL, resR, res);
    else if (hasL) copy_mat(resL, res);
    else if (hasR) copy_mat(resR, res);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    if (!(cin >> n >> q >> x)) return 0;
 
    d_arr.resize(n);
    for (int i = 0; i < n; ++i) cin >> d_arr[i];
 
    s_arr.resize(n);
    for (int i = 0; i < n; ++i) cin >> s_arr[i];
 
    SIZE = 1;
    while (SIZE < n) SIZE *= 2;
    tree.resize(SIZE * x * x, 0);
 
    build();
 
    for (int qi = 0; qi < q; ++qi) {
        char type;
        cin >> type;
        
        if (type == '1') {
            int i;
            long long v;
            cin >> i >> v;
            d_arr[i - 1] = v;
            if (i - 1 < SIZE) update(i - 1);
            
        } else if (type == '2') {
            int i;
            long long y;
            cin >> i >> y;
            s_arr[i - 1] = y;
            if (i - 1 < SIZE) update(i - 1);
            
        } else if (type == '?') {
            int l_idx, r_idx;
            cin >> l_idx >> r_idx;
            int l0 = l_idx - 1;
            int r0 = r_idx - 1;
            
            long long start_v[10];
            long long L_len = d_arr[l0];
            long long cost = s_arr[l0];
            
            for (int v = 0; v < x; ++v) {
                long long D = L_len - (v + 1);
                if (D < 0) {
                    start_v[v] = INF;
                } else if (D == 0) {
                    start_v[v] = 0;
                } else {
                    start_v[v] = ((D + x - 1) / x) * cost;
                }
            }
            
            long long final_res[100];
            query_range(l0 + 1, r0, final_res);
            
            long long ans = INF;
            for (int k = 0; k < x; ++k) {
                if (start_v[k] != INF && final_res[k * x + 0] != INF) {
                    long long val = start_v[k] + final_res[k * x + 0];
                    if (val < ans) ans = val;
                }
            }
            cout << ans << "
";
        }
    }
 
    return 0;
}