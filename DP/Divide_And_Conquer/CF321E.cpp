#include <iostream>
#include <vector>

using namespace std;

// 1. 极其重要的快读
inline int read() {
    int x = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x;
}

const int N = 4005;
const int INF = 1e9;
int n, k;
int w[N][N]; 
int cost[N][N]; 
int dp[805][N]; 

void precompute_costs() {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            
            cost[i][j] = cost[i][j - 1] + w[j][j] - w[j][i - 1];
        }
    }
}

void compute(int cur, int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) >> 1;
    int best_val = INF;
    int opt = -1;
    for (int i = optl; i <= min(mid, optr); i++) {
        int val = dp[cur - 1][i - 1] + cost[i][mid];
        if (val < best_val) {
            best_val = val;
            opt = i;
        }
    }

    dp[cur][mid] = best_val;
    compute(cur, l, mid - 1, optl, opt);
    compute(cur, mid + 1, r, opt, optr);
}

void solve()
{
    n = read(); k = read();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int val = read();
            w[i][j] = w[i][j - 1] + val;
        }
    }
    precompute_costs();
    for (int i = 1; i <= n; i++) {
        dp[1][i] = cost[1][i];
    }
    for (int i = 2; i <= k; i++) {
        compute(i, 1, n, 1, n);
    }
    printf("%d\n", dp[k][n]);
}

// #define _DEBUG
int main() 
{
#ifdef _DEBUG
    freopen("input.txt" ,"r" , stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    solve();
    return 0;
}