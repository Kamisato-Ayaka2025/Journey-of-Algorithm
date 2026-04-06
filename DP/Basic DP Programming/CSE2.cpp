#include <iostream>
using namespace std;
typedef long long LL;
const int N = 1e2 + 10 , M = 1e6 + 10 , mod = 1e9 + 7;
int n , m;
LL v[N];
LL dp[M];
// 考虑前 n 个数，组成 m 的方案数

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++) cin >> v[i];

    dp[0] = 1LL;
    for(int i = 1 ; i <= m ; i++){
        for(int j = 1 ; j <= n ; j++){
            if(i >= v[j]) dp[i] = (dp[i] + dp[i - v[j]]) % mod;
        }
    }

    cout << dp[m] << "\n";
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