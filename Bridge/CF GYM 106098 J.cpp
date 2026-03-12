#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

class Edge{
public:
    int from , to , eid;
    Edge(int f , int t , int id) : from(f) , to(t) , eid(id) {};

    inline int theOther(int x)
    {
        return from ^ to ^ x;
    }
};

const int N = 2e5 + 10, mod = 1e9 + 7;

int n , m;
vector<int> g[N];
vector<Edge> edge;

LL ans[N]; // 用来存每个点删掉每个边后可能的结果

int dfn[N] , low[N] , timer;
int sz[N];

void dfs(int u , int feid)
{
    sz[u] = 1;
    dfn[u] = low[u] = ++timer;
    for(int eid : g[u])
    {
        if(eid == feid) continue;
        
        int v = edge[eid].theOther(u);
        if(!dfn[v])
        {   // 一定是Spanning Edge
            dfs(v , eid);
            sz[u] += sz[v];
            low[u] = min(low[u] , low[v]);

            if(low[v] > dfn[u])
            {   // Bridge
                ans[u] = (ans[u] + n - sz[v]) % mod;
                ans[v] = (ans[v] + sz[v]) % mod;
            }
            else
            {   // SCC内部边
                ans[u] = (ans[u] + n) % mod;
                ans[v] = (ans[v] + n) % mod;
            }
        }
        else if(dfn[v] < dfn[u])
        {   // 一定是BackEdge
            // BackEdge不会有任何的影响
            low[u] = min(low[u] , dfn[v]);
            ans[u] = (ans[u] + n) % mod;
            ans[v] = (ans[v] + n) % mod;
        }
    }   
}

LL qmi(LL x , LL k)
{
    LL res = 1;
    while(k)
    {
        if(k & 1) res = (res * x) % mod;
        x = (x * x) % mod;
        k >>= 1;
    }
    return res;
}

void init()
{
    for(int i = 1 ; i <= n ; i++)
    {
        g[i].clear();
        sz[i] = dfn[i] = low[i] = 0;
        ans[i] = 0ll;
    }
    timer = 0;
    edge.clear();
}

void solve()
{
    cin >> n >> m;
    init();
    for(int i = 0 ; i < m ; i++)
    {
        int u , v;
        cin >> u >> v;
        edge.emplace_back(u , v , i);
        g[u].push_back(i);
        g[v].push_back(i);
    }

    dfs(1 , -1);

    LL res = 0;
    LL inv_n = qmi(n , mod - 2);
    for(int i = 1 ; i <= n ; i++)
    {
        LL point_expected = 0;
        if(g[i].empty())
        {   // 由于图是相连的，这个应该不存在
            point_expected = 1;
        }
        else
        {
            point_expected = ans[i] * qmi((LL)g[i].size() , mod - 2) % mod;
        }
        res = (res + point_expected * inv_n % mod ) % mod;
    }
    cout << res << "\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt"  ,"r" , stdin);
    freopen("output.txt"  , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while( T-- ) solve();
    return 0;
}