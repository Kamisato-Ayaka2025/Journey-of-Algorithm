#include <iostream>
using namespace std;
typedef long long LL;
const int N = 5e3 + 10, mod = 998244353;

int n , m;
LL dp[N]; // 考虑盒子里前 n 个数 ，和为 m 的方案

void solve()
{
    cin >> n >> m;
    dp[0] = 1ll;
    for(int i = 1 ; i <= n ; i++)
    {
        int x;
        char op[2];
        cin >> op >> x;
        if(op[0] == '+')
        {
            for(int j = m ; j >= x ; j--){
                dp[j] = (dp[j] + dp[j - x]) % mod;
            }
        }
        else
        {
            for(int j = x ; j <= m ; j++){
                dp[j] = (dp[j] - dp[j - x] + mod) % mod;
            }
        }
        cout << dp[m] << "\n";
    }
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