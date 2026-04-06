#include <iostream>
using namespace std;

const int N = 1e6 + 10 , mod = 1e9 + 7;
int n;
int dp[N];

void solve()
{
    dp[0] = 1;
    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = 1 ; j <= 6 && j <= i ; j++)
        {
            dp[i] = (dp[i] + dp[i - j]) % mod;
        }
    }
    cout << dp[n] << "\n";
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