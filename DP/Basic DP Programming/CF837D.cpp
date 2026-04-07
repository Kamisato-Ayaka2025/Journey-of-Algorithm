#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 210 ,  M = 6000;
int n , k;
int dp[N][M]; // 表示考虑前 n 个数 ，选择 k 个数 ，凑出 m 个因子 5 的最大因子2数量
int v1[N] , v2[N];

void solve()
{
    memset(dp , -0x3f , sizeof dp);
    cin >> n >> k;
    for(int i = 1 ; i <= n ; i++)
    {
        LL x;
        cin >> x;
        while(x % 2 == 0 && x){
            x /= 2;
            v1[i]++;
        }
        while(x % 5 == 0 && x){
            x /= 5;
            v2[i]++;
        }
    }
    
    dp[0][0] = 0;
    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = k ; j >= 0 ; j--)
        {
            for(int t = M ; t >= v2[i]; t--)
            {
                // 选
                if(j >= 1) dp[j][t] = max(dp[j][t] , dp[j - 1][t - v2[i]] + v1[i]);
            }
        }
    }

    int res = 0;
    for(int i = 0 ; i < M ; i++)
    {
        res = max(res , min(i , dp[k][i]));
    }
    cout << res << "\n";
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