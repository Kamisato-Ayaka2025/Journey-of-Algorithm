#include <iostream>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

int n , q;
vector<int> g[N];
int up[N][20] , depth[N];

void dfs(int u , int f)
{
    up[u][0] = f;
    for(int i = 1 ; i < 20 ; i++)
    {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }

    for(int v : g[u])
    {
        if(v == f) continue;
        depth[v] = depth[u] + 1;
        dfs(v , u);
    }
}

int lca(int a , int b)
{
    if(depth[a] < depth[b]) swap(a , b);
    int f = depth[a] - depth[b];
    
    for(int i = 19 ; i >= 0 ; i--)
    {
        if(f & (1 << i))
        {
            a = up[a][i];
        }
    }

    if(a == b) return a;
    for(int i = 19 ; i >= 0 ; i--)
    {
        if(up[a][i] != up[b][i])
        {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

void solve()
{
    cin >> n >> q;
    for(int i = 1 ; i < n ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    
    dfs(1 , 1);

    while( q-- )
    {
        bool ok = false;
        vector<int> v;
        
        int mx_node = 1 , mx_depth = -1;

        int k;
        cin >> k;
        for(int i = 1 ; i <= k ; i++)
        {
            int u;
            cin >> u;
            u = up[u][0];
            v.push_back(u);
            if(depth[u] > mx_depth)
            {
                mx_depth = depth[u];
                mx_node = u;
            }
        }

        for(auto u : v )
        {
            if(lca(u , mx_node) != u){
                ok = true;
                break;
            }
        }

        if(ok)
        {
            cout << "NO\n";
        }
        else cout << "YES\n";
    }
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt"  ,"r" , stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}