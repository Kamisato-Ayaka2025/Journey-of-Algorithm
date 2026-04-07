#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 410;
int n;
LL a[N] , sum[N];
LL dp[N][N];

void solve()
{
    memset(dp , 0x3f , sizeof dp);
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    for(int i = 1 ; i <= n ; i++) dp[i][i] = 0;

    for(int len = 2 ; len <= n ; len++)
    {
        for(int i = 1 ; i + len - 1 <= n ; i++)
        {
            int j = i + len - 1;
            for(int k = i ; k < j ; k++)
            {
                dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }

    cout << dp[1][n] << "\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r", stdin);
    freopen("output.txt" , "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}