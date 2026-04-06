#include <iostream>
using namespace std;

const int N = 510, M = (1 + N) * N / 2 , mod = 1e9 + 7;
int n , m;
int dp[M];

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++) m += i;
    if(m % 2){
        cout << 0 << "\n";
        return;
    } 
    m /= 2;
    dp[0]=  1;
    for(int i = 1 ; i < n ; i++)
    {
        for(int j = m ; j >= i ; j--)
        {
            dp[j] = (dp[j] + dp[j - i]) % mod;
        }
    }

    cout << dp[m]<< "\n";
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