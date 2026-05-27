#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 410;

class Trip{
public:
    int start , end , cost;
};

vector<vector<Trip>> trip;
int n , m;
int a[N];

int dp[2][N][N]; // 表示将 [l , r]切分 cnt 块的最长区间长度
int opt[N][N]; // opt[l][r] 表示将[l , r]切分成cnt块时的最优分割点

// dp[k][i][j] = min(max(dp[k - 1][i][m] , (a[j] - a[m]))) (m < j)

void solve()
{
    LL ans = 0;
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> a[i];
    }

    trip.resize(n + 1);

    for(int i = 1 ; i <= m ; i++)
    {
        int s , e , c , r;
        cin >> s >> e >> c >> r;
        r = min(r , n - 1);
        trip[r].push_back({s , e , c});
    }

    // 初始化
    for(int i = 1 ; i <= n ; i++)
    {
        opt[i][i] = i;
        for(int j = i + 1 ; j <= n ; j++)
        {
            dp[1][i][j] = a[j] - a[i];
            opt[i][j] = i;
        }
    }

    if(!trip[0].empty())
    {
        for(auto &t : trip[0])
        {
            int s = t.start , e = t.end , c = t.cost;
            ans = max(ans , (LL)dp[1][s][e] * c);
        }
    }

    // dp
    for(int k = 2 ; k <= n ; k++)
    {   // 遍历切割块数
        for(int i = n - 1 ; i >= 1 ; i--)
        {
            for(int j = i + 1 ; j <= n ; j++)
            {
                int minimum = 1e9;
                for(int m = opt[i][j - 1] ; m <= min(j - 1 , opt[i + 1][j]) ; m++)
                {
                    if(minimum > max(dp[(k - 1) & 1][i][m] , a[j] - a[m]))
                    {
                        minimum = max(dp[(k - 1) & 1][i][m] , a[j] - a[m]);
                        opt[i][j] = m;
                    }
                }
                dp[k & 1][i][j] = minimum;
            }
        }

        if(!trip[k - 1].empty())
        {
            for(auto &t : trip[k - 1])
            {
                int s = t.start , e = t.end , c = t.cost;
                ans = max(ans , (LL)dp[k & 1][s][e] * c);
            }
        }
    }
    cout << ans << "\n";
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