#include <iostream>
#include <vector>

using namespace std;

const int N = 3e5 + 10;

vector<int> g[N];
int n;
int up[N][20] , depth[N];

void dfs(int u , int f)
{   // 初始化
    up[u][0] = f;
    for(int i = 1 ; i < 20 ; i++){
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

int kth(int u , int k)
{
    for(int i = 0 ; i < 20 ; i++)
    {
        if(k & (1 << i)){
            u = up[u][i];
        }
    }
    return u;
}

void solve()
{
    cin >> n;
    for(int i = 1 ; i < n ; i++)
    {
        int u ,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1 , 0);

    int q;
    cin >> q;
    while( q-- )
    {
        int a , b , c;
        cin >> a >> b >> c;
        int x = lca(a , b);
        int len = depth[a] + depth[b] - 2 * depth[x];
        if(c >= len){
            cout << b << "\n";
        }
        else
        {
            if(c <= abs(depth[a] - depth[x])){
                cout << kth(a , c) << "\n";
            }
            else{
                int tmp = abs(c - (depth[a] -depth[x]));
                cout << kth(b , depth[b] - depth[x] - tmp) << "\n";
            }   
        }
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