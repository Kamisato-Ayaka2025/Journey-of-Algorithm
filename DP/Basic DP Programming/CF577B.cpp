#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e3 + 10;
int n , m;
int a[N];

bool dp[N][N]; // 考虑前 i 个数，能否找到子序列和模 m 等于 j

void solve()
{
    cin >> n >> m;
    if(n >= m){
        cout << "YES\n";
        return;
    }

    for(int i = 1 ; i <= n ; i++) cin >> a[i];

    for(int i = 1 ; i <= n ; i++)
    {
        // 不选a[i]
        for(int j = 0 ; j < m ; j++)
        {
            dp[i][j] = dp[i - 1][j];
        }
        for(int j = 0 ; j < m ; j++)
        {
            if(dp[i - 1][j])
            {
                dp[i][(j + a[i]) % m] = true;
            }
        }
        // 只选a[i]
        dp[i][a[i] % m] = true;
    }

    if(dp[n][0]) cout << "YES\n";
    else cout << "NO\n";
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