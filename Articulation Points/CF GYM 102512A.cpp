#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int N = 2e5 + 10;

int n , m;

vector<int> g[N];
vector<int> g1[N * 2]; // 新树

int dfn[N] , low[N] , timer;
stack<int> stk;
int  block_cnt;

int dep[N * 2] , fa[N * 2][20] , sum[N * 2];

void dfs(int u , int f = -1)
{   // Build Block Cut Tree
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    int children = 1;
    for(int v : g[u])
    {
        if(v == f) continue;
        if(dfn[v]){
            low[u] = min(low[u] , dfn[v]);
        }
        else
        {
            children++;
            dfs(v , u);
            low[u] = min(low[u] , low[v]);

            if(low[v] >= dfn[u])
            {
                block_cnt++;
                int node;
                do{
                    node = stk.top();
                    stk.pop();

                    g1[block_cnt].push_back(node);
                    g1[node].push_back(block_cnt);
                }while(node != v);

                g1[block_cnt].push_back(u);
                g1[u].push_back(block_cnt);
            }
        }
    }
}

void dfs_lca(int u , int f = 0)
{   // 准备LCA
    dep[u] = dep[f] + 1;
    
    fa[u][0] = f;
    for(int j = 1 ; j < 20 ; j++){
        fa[u][j] = fa[fa[u][j - 1]][j - 1];
    }

    sum[u] = sum[f] + (u <= n);

    for(int v : g1[u])
    {
        if(v == f) continue;
        dfs_lca(v , u);
    }
}

int lca(int a , int b)
{
    if(dep[a] < dep[b]) swap(a , b);
    int f = dep[a] - dep[b];
    for(int j = 19 ; j >= 0 ; j--){
        if(f & (1 << j)){
            a = fa[a][j];
        }
    }

    if(a == b) return a;

    for(int j = 19 ; j >= 0 ; j--){
        if(fa[a][j] != fa[b][j]){
            a = fa[a][j];
            b = fa[b][j];
        }
    }
    return fa[a][0];
}

void solve()
{
    cin >> n >> m;
    block_cnt = n + 1;
    for(int i = 1 ; i <= m ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);
    dfs_lca(1);

    int Q;
    cin >> Q;
    while( Q-- )
    {
        int C , D;
        cin >> C >> D;
        int x = lca(C , D);
        int ans = sum[C] + sum[D] - 2 * sum[x] + (x <= n);
        cout << max(0 , ans - 2) << "\n";
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
    return 0 ;
}