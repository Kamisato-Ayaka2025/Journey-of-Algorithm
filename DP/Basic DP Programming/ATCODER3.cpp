#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e5 + 10;
int n , k;
int h[N];
int dp[N];

void solve()
{
    memset(dp , 0x3f , sizeof dp);
    dp[1] = 0;
    cin >> n >> k;
    for(int i = 1 ; i <= n ; i++) cin >> h[i];

    for(int i = 2 ; i <= n ; i++)
    {
        for(int j = max(1 , i - k) ; j < i ; j++)
        {
            dp[i] = min(dp[i] , dp[j] + abs(h[i] - h[j]));
        }
    }

    cout << dp[n] << "\n";
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" ,"w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}