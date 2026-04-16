#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 3e3 + 10;
int k , n;
int a[N];
LL sum[N];

// dp[i][j]表示分割 i 次 在 前 j 个元素里面的最小开销
// dp[i][j] = min (dp[i - 1][k] + C(k , j));
LL dp[2][N];

LL C(int l , int r)
{
    return (sum[r] - sum[l - 1]) * (sum[r] - sum[l - 1]);
}

void compute(int cnt , int l , int r , int optl , int optr)
{
    if(l > r) return;

    int mid = (l + r) >> 1;
    pair<LL , int> best = {1e18 , -1};
    for(int i = optl ; i <= min(mid , optr) ; i++)
    {
        best = min(best , {dp[(cnt  - 1)& 1][i - 1] + C(i , mid), i});
    }

    dp[cnt & 1][mid] = best.first;
    int opt = best.second;
    compute(cnt , l , mid - 1, optl , opt);
    compute(cnt , mid + 1 , r , opt , optr);
}

void solve()
{
    cin >> n >> k;
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    for(int i = 1 ; i <= n ; i++)
    {
        dp[1][i] = C(1 , i);
    }

    for(int i = 2 ; i <= k ; i++)
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