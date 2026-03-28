#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 1e5+ 10;

int n , m;
vector<int> g[N];

int dfn[N] , low[N] , timer;
LL sz[N];

LL res = 0;

void dfs(int u , int f)
{
    sz[u] = 1;
    dfn[u] = low[u] = ++timer;
    for(int v : g[u])
    {
        if(v == f) continue;

        if(!dfn[v])
        {
            dfs(v , u);
            sz[u] += sz[v];
            low[u] = min(low[u] , low[v]);

            if(low[v] > dfn[u])
            {   // is_bridge
                LL s1 = sz[v];
                LL s2 = n - s1;
                res = min(res , (LL)n * (n - 1) / 2 - s1 * s2);
            }
        }
        else{
            low[u] = min(low[u] , dfn[v]);
        }
    }
}

void init()
{
    for(int i = 1 ; i <= n ; i++)
    {
        g[i].clear();
        low[i] = dfn[i] = 0;
        timer = 0;
        sz[i] = 0;
    }
    res = (LL)n * (n - 1) / 2;
}

void solve()
{
    cin >> n >> m;
    init();
    for(int i = 0 ; i < m ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1 , -1);
    cout << res << "\n";
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt"  ,"w" , stdout);
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