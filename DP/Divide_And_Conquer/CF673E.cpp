#include <iostream>
using namespace std;

const int N = 2e5 + 10;

int n , k;
// dp[i][j]表示考虑前 i 个游戏，将他们分成 j 个区域，所需要的期望尝试时间最小是
// dp[i][j] = min(dp[k - 1][j - 1] + C(k , j))
double dp[2][N];
double a[N] , sum[N] , sum1[N] , sum2[N];

void compute(int cnt , int l , int r , int optl , int optr)
{
    if(l > r) return;

    int mid = (l + r) >> 1;
    pair<double , int> best = {1e18 , -1};
    for(int i = optl ; i <= min(optr , mid) ; i++)
    {
        best = min(best , {dp[(cnt - 1)& 1][i - 1] + sum2[mid] - sum2[i - 1] - sum[i - 1] * (sum1[mid] - sum1[i - 1]), i});
    }

    dp[cnt & 1][mid] = best.first;
    int opt = best.second;

    compute(cnt , l , mid - 1 , optl , opt);
    compute(cnt , mid + 1 , r , opt , optr);
}

void solve()
{
    cin >> n >> k;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        sum1[i] = sum1[i - 1] + (1.0 / a[i]);
        sum2[i] = sum2[i - 1] + (sum[i] / a[i]);
    }

    // init
    for(int i = 1 ; i <= n ; i++)
    {
        dp[1][i] = dp[1][i - 1] + (sum[i] / a[i]);
    }

    for(int i = 2 ; i <= k ;i++)
    {
        compute(i , 1 , n , 1 , n);
    }
    cout << dp[k & 1][n] << "\n";
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