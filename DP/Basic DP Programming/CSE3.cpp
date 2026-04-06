#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e2 + 10 , M = 1e6 + 10;
int n , m;
int v[N];
int dp[M];

void solve()
{
    memset(dp , 0x3f , sizeof dp);
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i ++ ) cin >> v[i];

    dp[0] = 0;
    for(int i = 1 ; i <= m ; i++)
    {
        for(int j = 1 ; j <= n ; j++)
        {
            if(i >= v[j] && dp[i - v[j]] != 0x3f3f3f3f)
            {
                dp[i] = min(dp[i] , dp[i - v[j]] + 1);
            }
        }
    }

    cout << ((dp[m] == 0x3f3f3f3f) ? -1 : dp[m]) << "\n";
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