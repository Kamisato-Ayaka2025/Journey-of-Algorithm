#include <iostream>
#include <cstring>
using namespace std;

const int N = 110 , M = 1e5 + 10;
int n , m;
int dp[M]; // 考虑前 n 个元素， 价值为 m 对应的最小容量
int w[N] , v[N];
int sum;

void solve()
{
    memset(dp , 0x3f , sizeof dp);
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> w[i] >> v[i];
        sum += v[i];
    }

    dp[0] = 0;
    for(int i = 1 ; i <= n; i++)
    {
        for(int j = sum ; j >= v[i] ; j--)
        {
            dp[j] = min(dp[j] , dp[j - v[i]] + w[i]);
        }
    }

    int res = 0;
    for(int i = sum ; i >= 0 ; i--){
        if(dp[i] <= m){
            res = i;
            break;
        }
    }

    cout << res << "\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" ,"w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}