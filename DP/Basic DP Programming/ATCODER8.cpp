#include <iostream>
using namespace std;

const int N = 1e2 + 10 , M = 1e5 + 10;
int n , k;
int a[N];

int dp[M]; // 剩下 m 个石头时是必胜还是必败。

void solve()
{
    cin >> n >> k;
    for(int i = 1 ; i <= n ; i++) cin >> a[i];

    dp[0] = 0;
    for(int i = 1 ; i <= k ; i++)
    {
        for(int j = 1 ; j <= n ; j++)
        {
            if(i >= a[j] && dp[i - a[j]] == 0){
                dp[i] = 1;
                break;
            }
        }
    }
    if(dp[k]) cout << "First\n";
    else cout << "Second\n";
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