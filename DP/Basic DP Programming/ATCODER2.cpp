#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 10;

int n;
int dp[N];
int h[N];

void solve()
{
    memset(dp , 0x3f , sizeof dp);
    cin >> n;
    for(int i = 1 ; i <= n ; i++) cin >> h[i];

    dp[1] = 0;
    for(int i = 2 ; i <= n;  i++)
    {
        dp[i] = dp[i - 1] + abs(h[i] - h[i - 1]);
        if(i > 2) dp[i] = min(dp[i] , dp[i - 2] + abs(h[i] - h[i - 2]));
    }

    cout << dp[n] << "\n";
    return ;
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