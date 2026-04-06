#include <iostream>
#include <cstring>

using namespace std;
typedef long long LL;
const int N = 5e3 + 10;
int n;
LL a[N];
LL dp[N][N]; // 表示选到当前情况下最大能领先对手多少分
LL sum;

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> a[i];
        sum += a[i];
    }

    for(int i = 1 ; i <= n ; i++)
    {
        dp[i][i] = a[i];
    }

    for(int len = 2 ; len <= n ; len++)
    {
        for(int i = 1 ; i <= n - len + 1; i++)
        {
            int j = i + len - 1;
            dp[i][j] = max(a[i] - dp[i + 1][j] , a[j] - dp[i][j - 1]);
        }
    }

    cout << (sum + dp[1][n]) / 2 << "\n";
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