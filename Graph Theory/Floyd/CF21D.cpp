#include <iostream>
#include <vector>

using namespace std;

#define INF 1e9
typedef long long LL;
const int N = 20 , M = 2e3 + 10;

int n , m;
int dist[N][N] , p[N];
bool has_edge[N];

int in[N];

LL dp[1 << 16];

LL sum;

int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

inline int lowbit(int x){
    return x & -x;
}

int calc_pos(int x){
    for(int i = 1 ; i <= n ; i++){
        if(x >> i & 1){
            return i;
        }
    }
}

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++){
        p[i] = i;
        for(int j = 1 ; j <= n ; j++){
            dist[i][j] = INF;
        }
    }

    for(int i = 1 ; i <= m ; i++)
    {
        int u , v , w;
        cin >> u >> v >> w;

        dist[u][v] = min(dist[u][v] , w);
        dist[v][u] = min(dist[v][u] , w);
        sum += w;

        has_edge[u] = has_edge[v] = true;
        int root_u = find(u) , root_v = find(v);
        if(root_u != root_v)
        {
            p[root_u] = root_v;
        }

        in[v]++;
        in[u]++;
    }

    // 判断是否连通
    for(int i = 1 ; i <= n ; i++)
    {
        if(has_edge[i] && find(i) != find(1)){
            cout << "-1\n";
            return; 
        }
    }

    // Floyd
    for(int k = 1 ; k <= n ; k++)
    {
        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= n ; j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Init DP;
    int init_mask = 0;
    for(int i = 1 ; i <= n ; i++)
    {
        if(in[i] % 2){ // 入度为奇数是必定有边相连的
            init_mask |= (1 << i);
        }
    }

    for(int i = 0 ; i <= (1 << n + 1) - 1 ; i++){
        dp[i] = INF;
    }
    dp[init_mask] = sum;

    //DP
    for(int mask = init_mask ; mask > 0 ; mask--)
    {
        if(dp[mask] == INF) continue;
        int i = calc_pos(mask);
        for(int j = i + 1 ; j <= n ; j++)
        {
            if(mask >> j & 1)
            {
                int ne_mask = mask ^ (1 << i) ^ (1 << j);
                dp[ne_mask] = min(dp[ne_mask] , dp[mask] + dist[i][j]); 
            }
        }
    }

    cout << dp[0] << "\n";
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