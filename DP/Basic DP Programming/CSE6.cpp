#include <iostream>
using namespace std;

const int N = 1e3 + 10 , M = 1e5 + 10;
int n , m;
int dp[M];
int v[N] , w[N];

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++) cin >> v[i];
    for(int i = 1 ; i <= n ; i++) cin >> w[i];

    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = m ; j >= v[i] ; j--)
        {
            dp[j] = max(dp[j] , dp[j - v[i]] + w[i]);
        }
    }

    cout << dp[m] << "\n";
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