#include <iostream>
using namespace std;

typedef long long LL;
const int N = 1e2 + 10 , M = 1e5 + 10;
int n , m;
LL dp[N][M];
int w[N] , v[N];

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> w[i] >> v[i];
    }

    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = 0 ; j <= m ; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if(j >= w[i]){
                dp[i][j] = max(dp[i][j] , dp[i - 1][j - w[i]] + (LL)v[i]);
            }
        }
    }

    cout << dp[n][m] << "\n";
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