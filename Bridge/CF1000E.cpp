#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int N = 3e5 + 10;

class Edge{
public:
    int from , to , edgeID;
    Edge(int f , int t , int eid) : from(f) , to(t) , edgeID(eid) {};

    inline int theOther(int x){
        return from ^ to ^ x;
    }
};

int n , m;
vector<int> g[N];
vector<Edge>edge;

int dfn[N] , low[N] , timestamp;
stack<int> stk;

vector<int> g1[N]; // 新树

int comp_cnt , id[N];
int depth[N];

void dfs(int u , int f)
{
    dfn[u] = low[u] = ++timestamp;
    stk.push(u);

    for(int eid : g[u])
    {
        if(eid == f) continue;
        int v = edge[eid].theOther(u);
        
        if(!dfn[v])
        {
            dfs(v , eid);
            low[u] = min(low[u] , low[v]);
        }
        else{
            low[u] = min(low[u] , dfn[v]);
        }
    }

    if(low[u] == dfn[u])
    {
        comp_cnt++;
        while(true)
        {
            int t = stk.top();
            stk.pop();

            id[t] = comp_cnt;

            if(t == u) break;
        }
    }
}

void dfs1(int u , int f , int *depth)
{   
    for(int v : g1[u])
    {
        if(v == f) continue;
        depth[v] = depth[u] + 1;
        dfs1(v , u , depth);
    }
}   

void solve()
{
    cin >> n >> m;
    for(int i = 0 ; i < m ; i++)
    {
        int u , v;
        cin >> u >> v;
        edge.emplace_back(u , v , i);
        g[u].push_back(i);
        g[v].push_back(i);
    }

    dfs(1 , -1);

    for(int i = 0 ; i < m ; i++)
    {
        auto e = edge[i];
        int u = e.from , v = e.to;
        if(id[u] != id[v]){
            g1[id[u]].push_back(id[v]);
            g1[id[v]].push_back(id[u]);
        }
    }

    // 然后找直径
    dfs1(1 , 0 , depth);
    
    int mx_depth = -1 , mx_node = 1;
    for(int i = 1 ; i <= comp_cnt ; i++)
    {
        if(depth[i] >= mx_depth)
        {
            mx_depth = depth[i];
            mx_node = i;
        }
    }
    int a = mx_node;

    mx_depth = -1 , depth[mx_node] = 0;
    dfs1(mx_node , -1 , depth);
    for(int i = 1 ; i <= comp_cnt ; i++)
    {
        if(depth[i] >= mx_depth)
        {
            mx_depth = depth[i];
            mx_node = i;
        }
    }
    int b = mx_node;

    cout << depth[b] << "\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" ,"r" , stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}