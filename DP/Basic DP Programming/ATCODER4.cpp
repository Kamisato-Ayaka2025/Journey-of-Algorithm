#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3e3 + 10;
int n , m;
string a , b;
int dp[N][N]; // 考虑序列1的前i个元素和序列2的前j个元素的最长公共子序列长度

void solve()
{
    cin >> a >> b;
    a = " " + a;
    b = " " + b;
    n = a.size() - 1;
    m = b.size() - 1;

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m  ;j++){
            if(a[i] == b[j]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else{
                dp[i][j] = max(dp[i - 1][j] , dp[i][j - 1]);
            }
        }
    }

    string res = "";
    int i = n , j = m;
    while (i > 0 && j > 0)
    {
        if(a[i] == b[j]){
            res += a[i];
            i--;
            j--;
        }
        else if(dp[i - 1][j] > dp[i][j - 1]){
            i--;
        }
        else j--;
    }
    reverse(res.begin() , res.end());
    cout << res << "\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" , "w" ,  stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}