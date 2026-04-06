#include <iostream>
#include <vector>
using namespace std;

const int N = 110 , M = 1e5 + 10;
int n , m;
int v[N];
bool dp[M]; // 考虑前 n 个元素，能否凑出j

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> v[i]; 
        m += v[i];
    } 

    dp[0] = true;
    for(int i = 1 ; i <= n ; i++){
        for(int j = m ; j >= v[i] ; j--){
            if(dp[j - v[i]]) dp[j] = true;
        }
    }

    vector<int> res;
    for(int i = 1 ; i <= m ; i++){
        if(dp[i]){
            res.push_back(i);
        }
    }

    cout << res.size() << "\n";
    for(int v : res) cout << v << " ";
    cout << "\n";
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