#include <iostream>
#include <iomanip>
using namespace std;

const int N = 3e3 + 10;
int n;
double dp[N]; // 考虑前 i 个硬币，有 j 个硬币朝上的概率.
double p[N];
void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> p[i];
    }

    dp[0] = 1.0; // 没有硬币，朝上和朝下的概率都是 1.0
    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = i ; j >= 1 ; j--){
            dp[j] = dp[j - 1] * p[i] + dp[j] * (1 - p[i]);
        }
        dp[0] = dp[0] * (1 - p[i]); // 第 i 个硬币继续朝下
    }

    double res = 0.0;
    for(int i = n / 2 + 1 ; i <= n ; i++){
        res += dp[i];
    }

    cout << fixed << setprecision(10) << res << "\n";
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