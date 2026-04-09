#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;
const int N = 110 , M = 2e4 + 10;;
int n;
LL res , sum , sum_of_square;
int a[N] , b[N];
int dp[2][M]; // 考虑 a 的前 i 个元素，是否可以凑出数值 j

void solve()
{
    memset(dp , 0 , sizeof dp);
    res = sum = sum_of_square = 0ll;

    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
        sum += a[i];
        sum_of_square += (LL)a[i] * a[i];
    }
    for(int i = 1 ; i <= n ; i++){
        cin >> b[i];
        sum += b[i];
        sum_of_square += (LL)b[i] * b[i];
    }
    res = sum_of_square * (n - 1);
    // (\sum a) ^ 2 + (\sum b) ^ 2
    // (\sum a) ^ 2 + (S - \sum a)^2
    dp[0][0] = true;
    for(int i = 1 ; i <= n; i++)
    {
        for(int j = sum ; j >= 0 ; j--)
        {
            if(j >= a[i] && dp[(i - 1) & 1][j - a[i]]){
                dp[i & 1][j] = true;
            }
            else if(j >= b[i] && dp[(i - 1) & 1][j - b[i]]){
                dp[i & 1][j] = true;
            }
            else{
                dp[i & 1][j] = false;
            }
        }
    }

    LL ans = 0;
    for(int i = sum / 2 ; i >= 0 ; i--){
        if(dp[n & 1][i]){
            ans = i;
            break;
        }
    }
    res = res + ans * ans + (sum - ans) * (sum - ans) - sum_of_square;
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

    int T;
    cin >> T;
    while( T-- ){
        solve();
    }
    return 0;
}