#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define INF 0x3f3f3f3f
const int N = 3e5 + 10;

int n , m;
int e[N * 2] , h[N] , ne[N * 2] , idx , w[N * 2];

int up[N][20] , depth[N] , min_edge[N][20];

void addEdge(int a , int b , int c)
{
    e[idx] = b , ne[idx] = h[a] , w[idx] = c , h[a] = idx++; 
}

void dfs(int u , int f , int edge_w)
{
    up[u][0] = f;
    min_edge[u][0] = edge_w;
    for(int i = 1 ; i < 20 ; i++)
    {
        up[u][i] = up[up[u][i - 1]][i - 1];
        min_edge[u][i] = min(min_edge[u][i - 1] , min_edge[up[u][i - 1]][i - 1]);
    }

    for(int i = h[u] ; ~i ; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        depth[j] = depth[u] + 1;
        dfs(j , u , w[i]);
    }
}

int lca(int a , int b)
{
    if(depth[a] < depth[b]) swap(a , b);
    int f = depth[a] - depth[b];
    for(int i = 19 ; i >= 0 ; i--)
    {
        if(f & (1 << i)){
            a = up[a][i];
        }
    }

    if(a == b) return a;
    for(int i = 19 ; i >= 0 ; i--)
    {
        if(up[a][i] != up[b][i]){
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

int get_min(int u , int anc)
{
    int res = INF;
    int dist = depth[u] - depth[anc];
    for(int i = 19 ; i >= 0 ; i--)
    {
        if(dist & (1 << i)){
            res = min(res , min_edge[u][i]);
            u = up[u][i];
        }
    }
    return res;
}

void solve()
{
    memset(h , -1 , sizeof h);
    memset(min_edge , 0x3f , sizeof min_edge);
    cin >> n >> m;
    for(int i = 1 ; i <= m ; i++)
    {
        int u , v , w;
        cin >> u >> v >> w;
        addEdge(u , v , w);
        addEdge(v , u , w);
    }
    
    dfs(1 , 0 , INF);
    int q;
    cin >> q;
    while( q-- )
    {
        int u , v;
        cin >> u >> v;
        int x = lca(u , v);
        cout << min(get_min(u , x) , get_min(v , x)) << "\n";
    }
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