#include <iostream>
#include <algorithm>

using namespace std;

#define INF 1e18
typedef long long LL;

const int N = 5e3 + 10;
// 表示将 [l , r]切分到最小块的最小cost
// dp[i][j] = min(dp[i][k] + dp[k + 1][j] + C(i , j))
LL dp[N][N];
int opt[N][N];

int n;
int a[N];
LL sum[N];

LL C(int l , int r)
{
    return sum[r] - sum[l - 1];
}

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    // init
    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = i + 1 ; j <= n ; j++)
        {
            dp[i][j] = INF;
        }
    }
    
    for(int i = 1 ; i <= n ; i++)
    {
        opt[i][i] = i;
        dp[i][i] = 0;
    }

    for(int i = n - 1 ; i >= 1 ; i--)
    {
        for(int j = i + 1 ; j <= n ; j++)
        {
            LL maximum = INF;
            for(int k = opt[i][j - 1] ; k <= min(j - 1  , opt[i + 1][j]) ; k++)
            {
                if(maximum > dp[i][k] + dp[k + 1][j] + C(i , j))
                {
                    maximum = dp[i][k] + dp[k + 1][j] + C(i , j);
                    opt[i][j] = k;
                }
            }
            dp[i][j] = maximum;
        }
    }

    cout << dp[1][n] << "\n";
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