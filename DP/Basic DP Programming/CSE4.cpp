#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e6 + 10;
int n;
int dp[N];

void solve()
{
    memset(dp , 0x3f , sizeof dp);
    cin >> n;
    dp[n] = 0;
    for(int i = n ; i > 0 ; i--)
    {
        int num = i;
        if(dp[i] == 0x3f3f3f3f) continue;
        while(num)
        {
            int t = num % 10;
            num /= 10;
            if(i >= t)dp[i - t] = min(dp[i - t] , dp[i] + 1);
        }
    }

    cout << dp[0] << "\n";
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