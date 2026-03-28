#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1e5 + 10;
int n , k;
vector<int> g[N];
vector<int> g1[N];
int depth[N] , parent[N][20];
int dfn[N] , timer;

int chosen[N];
bool isKey[N];
int sz[N] , cost[N];

void dfs_pre(int u , int f)
{
    dfn[u] = ++timer;
    depth[u] = depth[f] + 1;
    // LCA
    parent[u][0] = f;
    for(int j = 1 ; j < 20 ; j++){
        parent[u][j] = parent[parent[u][j - 1]][j - 1];
    }

    for(int v : g[u])
    {
        if(v == f) continue;
        dfs_pre(v , u);
    }
}

int lca(int a , int b)
{
    if(depth[a] < depth[b]) swap(a , b);
    int f = depth[a] - depth[b];
    for(int j = 19 ; j >= 0 ; j--)
    {
        if(f & (1 << j))
        {
            a = parent[a][j];
        }
    }

    if(a == b) return a;
    for(int j = 19 ; j >= 0 ; j--)
    {
        if(parent[a][j] != parent[b][j])
        {
            a = parent[a][j];
            b = parent[b][j];
        }
    }
    return parent[a][0];
}

bool cmp(int a , int b)
{
    return dfn[a] < dfn[b];
}

int build_Virtual_Tree()
{
    // 排序 求LCA + 去重
    int len = k;
    sort(chosen + 1 , chosen + 1 + k , cmp);
    for(int i = 1 ; i < k ; i++)
    {
        chosen[++len] = lca(chosen[i] , chosen[i + 1]);
    }
    sort(chosen + 1 , chosen + 1 + len , cmp);
    int unique = 1;
    for(int i = 2 ; i <= len ; i++)
    {
        if(chosen[i] != chosen[unique]){
            chosen[++unique] = chosen[i];
        }
    }
    for(int i = 1 ; i <= unique ; i++) g1[chosen[i]].clear();
    //建立新树
    for(int i = 2 ; i <= unique ; i++)
    {
        g1[lca(chosen[i - 1] , chosen[i])].push_back(chosen[i]);
    }
    return chosen[1];
}

void dfs(int u)
{
    sz[u] = cost[u] = 0;
    for(int v : g1[u])
    {
        dfs(v);
        sz[u] += sz[v];
        cost[u] += cost[v];
    }

    if(isKey[u])
    {
        cost[u] += sz[u];
        sz[u] = 1;
    }
    else
    {
        if(sz[u] > 1){
            cost[u] += 1;
            sz[u] = 0;
        }
    }
}

void solve()
{
    cin >> n;
   
    for(int i = 1 ; i < n;  i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_pre(1 , 0);
    int q;
    cin >> q;
    while( q-- )
    {
        cin >> k;
        vector<int> query(k + 1);
        for(int i = 1 ; i <= k ; i++){
            cin >> chosen[i];
            query[i] = chosen[i];
            isKey[chosen[i]] = true;
        }
        bool check = false;
        for(int i = 1 ; i <= k ; i++){
            if(isKey[parent[chosen[i]][0]]){
                check = true;
                break;
            }
        }

        if(check){
            cout << "-1\n";
        }
        else{
            int root = build_Virtual_Tree();
            dfs(root);
            cout << cost[root] << "\n";
        }

        for(int i = 1 ; i <= k ; i++)
        {
            isKey[query[i]] = false;
        }
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