#include <iostream>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10 , M = 110 , mod = 1e9 + 7;
int n , m;
LL dp[N][M]; // 考虑前 n 个元素，最后一个元素是 j 的方案数
int a[N];

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++) cin >> a[i];

    // 初始化
    if(a[1] == 0){
        for(int j = 1 ; j <= m ; j++) dp[1][j] = 1ll;
    } else {
        dp[1][a[1]] = 1ll;
    }

    for(int i = 2 ; i <= n ; i++){
        if(a[i] == 0){
            for(int j = 1 ; j <= m ; j++){
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]) % mod;
            }
        }
        else{
            dp[i][a[i]] = (dp[i - 1][a[i] - 1] + dp[i - 1][a[i]] + dp[i - 1][a[i] + 1]) % mod;
        }
    }

    LL res = 0;
    if(a[n] == 0){
        for(int j = 1 ; j <= m ; j++) res = (res + dp[n][j]) % mod;
    }
    else{
        res = dp[n][a[n]];
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