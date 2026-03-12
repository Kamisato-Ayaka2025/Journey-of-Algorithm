#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int N = 2e5 + 10;

class Edge{
public:
    int from , to , eid;
    Edge(int f , int t , int eid) : from(f) , to(t) , eid(eid) {};

    inline int theOther(int x)
    {
        return from ^ to ^ x;
    }
};

int n , m , q;

int dfn[N] , low[N] , timer;
int id[N] , scc_cnt; // id表示属于哪个SCC
int comp[N] , comp_cnt; // 表示属于哪个连通分量

// 老图
vector<int> g[N];
vector<Edge> edge;

// 新树
vector<int> g1[N];
vector<Edge> edge1;

// 用来存root
vector<int> root;

stack<int> stk;

// 树上差分
int up_s[N] , down_s[N];

// LCA相关
int depth[N] , up[N][20];

bool ok = true;

// Tarjan
void dfs(int u , int feid , int comp_cnt)
{
    comp[u] = comp_cnt;

    dfn[u] = low[u] = ++timer;
    stk.push(u);

    for(int eid : g[u])
    {
        if(eid == feid) continue;
        int v = edge[eid].theOther(u);

        if(!dfn[v])
        {
            dfs(v , eid , comp_cnt);
            low[u] = min(low[u] , low[v]);
        }   
        else
        {
            low[u] = min(low[u] , dfn[v]);
        }
    }

    if(low[u] == dfn[u])
    {
        scc_cnt++;
        while(true)
        {
            int node = stk.top();
            stk.pop();

            id[node] = scc_cnt;
            if(node == u) break;
        }
    }
}

// LCA
void dfs_lca(int u , int f)
{   // 初始化LCA相关
    up[u][0] = f;
    for(int j = 1 ; j < 20 ; j++)
    {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }

    for(int eid : g1[u])
    {
        int v = edge1[eid].theOther(u);
        if(v == f) continue;
        depth[v] = depth[u] + 1;
        dfs_lca(v , u);
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
            a = up[a][j];
        }
    }

    if(a == b) return a;

    for(int j = 19 ; j >= 0 ; j--)
    {
        if(up[a][j] != up[b][j])
        {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

// 统计差分结果
void dfs_calc(int u , int f)
{
    for(int eid : g1[u])
    {
        int v = edge1[eid].theOther(u);
        if(v == f) continue;

        dfs_calc(v , u);
        up_s[u] += up_s[v];
        down_s[u] += down_s[v];
    }

    if(up_s[u] && down_s[u] && u ) // 还是排除一下根节点
    {
        ok = false;
    }   
}

void solve()
{
    cin >> n >> m >> q;
    for(int i = 0 ; i < m ; i++)
    {
        int u , v;
        cin >> u >> v;
        edge.emplace_back(u , v , i);
        g[u].push_back(i);
        g[v].push_back(i);
    }

    for(int i = 1 ; i <= n ; i++)
    {
        if(!dfn[i]) {
            dfs(i , -1 , ++comp_cnt);
            root.push_back(id[i]);
            // root直接存转化后的点
        }
    }

    // 构建新树
    int idx = 0;
    for(int i = 0 ; i < m ; i++)
    {
        int u = edge[i].from , v = edge[i].to;
        if(id[u] != id[v])
        {
            edge1.emplace_back(id[u] , id[v] , idx);
            g1[id[u]].push_back(idx);
            g1[id[v]].push_back(idx);
            idx++;
        }
    }

    // 我们设立一个统一的根节点，方便后面进行树上差分
    for(auto v : root){
        edge1.emplace_back(0 , v , idx);
        g1[0].push_back(idx);
        g1[v].push_back(idx);
        idx++;
    }
    dfs_lca(0 , 0);
 
    while( q-- )
    {
        int s , d;
        cin >> s >> d;
        
        if(comp[s] != comp[d]){
            // 不用写了 包错的
            ok = false;
            break;
        }

        s = id[s] , d = id[d];
        if(s == d) continue; // 直接不用差分，包对的

        int x = lca(s , d);

        // 差分
        up_s[s]++ , up_s[x]--;
        down_s[d]++ , down_s[x]--;
    }

    dfs_calc(0 , 0);
    if(ok) cout << "Yes\n";
    else cout << "No\n";
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt " ,"r" , stdin);
    freopen("output.txt"  ,"w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}