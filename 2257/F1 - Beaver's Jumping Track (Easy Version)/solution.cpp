#include <iostream>
#include <vector>
 
using namespace std;
 
const long long INF = 3e18;
 
// Matrix to hold transition costs between the boundary states.
struct Matrix {
    long long mat[5][5];
    Matrix() {
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                mat[i][j] = INF;
    }
};
 
// (min, +) Matrix Multiplication
Matrix multiply(const Matrix& A, const Matrix& B, int x) {
    Matrix C;
    for (int i = 0; i < x; ++i) {
        for (int k = 0; k < x; ++k) {
            if (A.mat[i][k] == INF) continue;
            for (int j = 0; j < x; ++j) {
                if (B.mat[k][j] == INF) continue;
                long long sum = A.mat[i][k] + B.mat[k][j];
                if (sum < C.mat[i][j]) {
                    C.mat[i][j] = sum;
                }
            }
        }
    }
    return C;
}
 
// Constructs the transition matrix for a platform of length d and penalty s
Matrix build_T(long long d, long long s, int x) {
    Matrix T;
    for (int j = 0; j < x; ++j) {
        if (j >= d) {
            int k = j - d;
            if (k >= 0 && k < x) {
                T.mat[k][j] = 0;
            }
        } else {
            for (int k = 0; k < x; ++k) {
                long long D = d - j + k;
                long long jumps = (D + x - 1) / x - 1;
                if (jumps < 0) jumps = 0;
                T.mat[k][j] = s * jumps;
            }
        }
    }
    return T;
}
 
// Constructs the initial state vector starting from the first cell of a platform
vector<long long> build_V(long long d, long long s, int x) {
    vector<long long> V(x, INF);
    for (int j = 0; j < x; ++j) {
        long long D = d - 1 - j;
        if (D >= 0) {
            long long jumps = (D + x - 1) / x;
            V[j] = s * jumps;
        }
    }
    return V;
}
 
// Vector-Matrix Multiplication for the final state
vector<long long> multiply_VM(const vector<long long>& V, const Matrix& M, int x) {
    vector<long long> res(x, INF);
    for (int j = 0; j < x; ++j) {
        for (int k = 0; k < x; ++k) {
            if (V[k] != INF && M.mat[k][j] != INF) {
                long long sum = V[k] + M.mat[k][j];
                if (sum < res[j]) {
                    res[j] = sum;
                }
            }
        }
    }
    return res;
}
 
// Global segment tree array
Matrix tree[2000005];
 
// Point update on iterative segment tree
void update(int p, const Matrix& val, int n, int x) {
    for (tree[p += n] = val; p > 1; p >>= 1) {
        // Ensures standard left-to-right associativity regardless of whether p is left or right child
        tree[p >> 1] = multiply(tree[p & ~1], tree[p | 1], x);
    }
}
 
// Range product query
Matrix query(int l, int r, int n, int x) {
    Matrix resL, resR;
    // Set both accumulators to the Identity matrix for (min, +) algebra
    for (int i = 0; i < x; ++i) {
        resL.mat[i][i] = 0;
        resR.mat[i][i] = 0;
    }
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) resL = multiply(resL, tree[l++], x);
        if (r & 1) resR = multiply(tree[--r], resR, x);
    }
    return multiply(resL, resR, x);
}
 
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, q, x;
    if (!(cin >> n >> q >> x)) return 0;
 
    vector<long long> D(n), S(n);
    for (int i = 0; i < n; ++i) cin >> D[i];
    for (int i = 0; i < n; ++i) cin >> S[i];
 
    // Build the Segment Tree leaves
    for (int i = 0; i < n; ++i) {
        tree[n + i] = build_T(D[i], S[i], x);
    }
    
    // Build upper layers of the Segment Tree
    for (int i = n - 1; i > 0; --i) {
        tree[i] = multiply(tree[i << 1], tree[i << 1 | 1], x);
    }
 
    // Process queries
    for (int i = 0; i < q; ++i) {
        char type;
        cin >> type;
        if (type == '1') {
            int idx; long long v;
            cin >> idx >> v;
            --idx; // Convert to 0-indexed
            D[idx] = v;
            update(idx, build_T(D[idx], S[idx], x), n, x);
        } else if (type == '2') {
            int idx; long long y;
            cin >> idx >> y;
            --idx; // Convert to 0-indexed
            S[idx] = y;
            update(idx, build_T(D[idx], S[idx], x), n, x);
        } else if (type == '?') {
            int l, r;
            cin >> l >> r;
            --l; --r; // Convert to 0-indexed limits
            
            // Generate exact state starting cleanly at platform `l`
            vector<long long> V = build_V(D[l], S[l], x);
            
            if (l == r) {
                cout << V[0] << "
";
            } else {
                // Determine matrices required for the remainder of the route
                Matrix M = query(l + 1, r + 1, n, x);
                vector<long long> ans = multiply_VM(V, M, x);
                cout << ans[0] << "
";
            }
        }
    }
 
    return 0;
}