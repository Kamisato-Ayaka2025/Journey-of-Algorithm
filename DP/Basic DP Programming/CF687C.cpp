#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
const int N = 510;
bool dp[N][N]; // 表示分给Araya i 钱，而子集为 x元钱的方案是否存在

void solve() {
    int n, k;
    cin >> n >> k;
    dp[0][0] = true;

    for (int i = 1; i <= n ; i++) {
        int v; 
        cin >> v;
        for (int j = k; j >= v; j--) {
            for (int x = j; x >= 0; x--) {
                if (dp[j - v][x]) dp[j][x] = true;
                if (x >= v && dp[j - v][x - v]) dp[j][x] = true;
            }
        }
    }

    vector<int> res;
    for (int x = 0; x <= k; x++) {
        if (dp[k][x]) res.push_back(x);
    }
    
    cout << res.size() << "\n";
    for(int x : res) cout << x << " ";
    return ;
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