#include <iostream>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

int n;
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
        if(f & (1 << i)){
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
    cin >> n;
    for(int i = 1 ; i < n ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1 , 0);
    int q;
    cin >> q;
    while( q-- )
    {
        bool ok = false;
        vector<int> vec;
        
        int k;
        cin >> k;

        // 寻找最深点
        int mx_node = 1 , mx_depth = -1;
        for(int i = 1 ; i <= k ; i++)
        {
            int u;
            cin >> u;
            vec.push_back(u);
            if(depth[u] > mx_depth){
                mx_depth = depth[u];
                mx_node = u;
            }
        }
        int a = mx_node;
        // 次深点   
        mx_depth = -1 , mx_node = 1;
        for(int i = 0 ; i < k ; i++)
        {
            int node = vec[i];
            if(depth[node] > mx_depth && lca(node , a) != node)
            {
                mx_depth = depth[node];
                mx_node = node;
            }
        }
        int b = mx_node;
        if(b == 1){
            cout << "YES\n";
            continue;
        }

        for(int v : vec)
        {
            if(v != a && v != b)
            {
                if((lca(v , a)  != v && lca(v , b) != v) || depth[v] < depth[lca(a , b)]){
                    ok = true;
                    break;
                }
            }
        }

        if(ok) cout << "NO\n";
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