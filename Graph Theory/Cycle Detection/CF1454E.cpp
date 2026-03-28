#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

typedef long long LL;

int n;
vector<int> g[N];
int dfn[N] , fa[N];
bool is_on_cycle[N];
vector<int> cycle;

LL sz[N];

bool dfs(int u , int f)
{
    dfn[u] = 1;
    fa[u] = f;
    for(int v : g[u])
    {
        if(v == f) continue;
        if(dfn[v] == 1)
        {
            int node = u;
            while(node != v){
                is_on_cycle[node] = true;
                cycle.push_back(node);
                node = fa[node];
            }

            is_on_cycle[v] = true;
            cycle.push_back(v);
            return true;
        }
        else if(!dfn[v]){
            if(dfs(v , u)) return true;
        }
    }
    dfn[u] = 2;
    return false;
}

void dfs_sz(int u , int f , int idx)
{
    sz[idx]++;
    for(int v : g[u])
    {
        if(v == f || is_on_cycle[v]) continue;
        dfs_sz(v , u , idx);
    }
}

void init()
{
    for(int i = 1 ; i <= n ; i++){
        g[i].clear();
        is_on_cycle[i] = false;
        sz[i] = 0ll;
        dfn[i] = fa[i] = 0;
    }
    sz[0] = 0ll;

    cycle.clear();
}

void solve()
{
    cin >> n;
    init();
    for(int i = 1 ; i <= n ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1 , 0);

    LL res = (LL)n * (n - 1);

    int k = cycle.size();
    for(int i =  0; i < k ; i++)
    {
        dfs_sz(cycle[i] , 0 , i);
        res -= sz[i] * (sz[i] - 1) / 2;
    }
    cout << res << "\n";
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

    int T;
    cin >> T;
    while( T-- ) solve();
    return 0;
}