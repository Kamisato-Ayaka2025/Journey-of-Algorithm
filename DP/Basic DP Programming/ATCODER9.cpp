#include <iostream>
using namespace std;
const int N = 110 , M = 1e5 + 10 , mod = 1e9 + 7;
int n , m;
int dp[N][M]; // 考虑前 i 组分了 m 个糖果的方案数

void solve()
{
    cin >> n >> m;
    for(int i = 0 ; i <= n ; i++) dp[i][0] = 1;

    for(int i = 1 ; i <= n ; i++)
    {
        int x;
        cin >> x;
        for(int j = 1 ; j <= m ; j++)
        {
            dp[i][j] =( dp[i - 1][j] + dp[i][j - 1]) % mod;
            if(j > x) dp[i][j] = (dp[i][j] - dp[i - 1][j - x - 1] + mod) % mod;
        }
    }

    cout << dp[n][m] << "\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" ,"r" , stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}