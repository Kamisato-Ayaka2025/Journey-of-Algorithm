#include <iostream>
using namespace std;

const int N = 110 , M = 1e6 + 10 , mod = 1e9 + 7;
typedef long long LL;
int n , m;
int v[N];
LL dp[2][M]; // 用前 n 种硬币组合成 m 的方案数

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++){
        cin >> v[i];
    }

    dp[0][0] = 1ll;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 0 ; j <= m ; j++){
            dp[i & 1][j] = dp[(i - 1) & 1][j];
            if(j >= v[i]) dp[i & 1][j] = (dp[i & 1][j] + dp[i & 1][j - v[i]]) % mod;
        }
    }
    
    cout << dp[n & 1][m] << "\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}