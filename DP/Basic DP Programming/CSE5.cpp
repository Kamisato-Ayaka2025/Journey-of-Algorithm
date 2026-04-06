#include <iostream>
using namespace std;

const int N = 1e3 + 10 , mod = 1e9 + 7;
int n;
int dp[N][N];
char map[N][N];

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> map[i] + 1;
    }

    dp[1][1] = (map[1][1] == '*') ? 0 : 1;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            if(map[i][j] == '*') continue;
            if(i == 1 && j == 1) continue;
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
        }
    }

    cout << dp[n][n] << "\n";
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