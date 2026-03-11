#include <iostream>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

const int N = 3e5 + 10;

class Edge{
public:
    int from , to , weight , edgeID;

    Edge(int f , int t , int w, int eid) : from(f) , to(t) , weight(w) , edgeID(eid) {};

    inline int theOther(int x)
    {
        return from ^ to ^ x;
    }
};

int n , m;
vector<int> g[N];
vector<Edge> edge;

int dfn[N] , low[N] , timestamp;
stack<int> stk;

int h[N] , e[N * 2] , ne[N * 2], w[N * 2] , idx;
int w_point[N];

int comp_cnt , id[N];
int depth[N];

void addEdge(int a , int b , int c)
{
    e[idx] = b , ne[idx] = h[a] , w[idx] = c , h[a] = idx++;
}

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

void dfs1(int u , int f)
{
    for(int i = h[u] ; ~i ; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        depth[j] = depth[u] | w[i] | w_point[j];
        dfs1(j , u);
    }
}

void solve()
{
    memset(h , -1 , sizeof h);
    cin >> n >> m;
    for(int i = 0 ; i < m ; i++)
    {
        int x , y , z;
        cin >> x >> y >> z;
        edge.emplace_back(x , y , z , i);
        g[x].push_back(i);
        g[y].push_back(i);
    }

    // 缩点 建新图
    dfs(1 , -1);
    for(int i = 0 ; i < m ; i++)
    {
        auto e = edge[i];
        int u = e.from , v = e.to , w_ = e.weight;
        if(id[u] == id[v])
        {
            w_point[id[u]] |= w_;
        }
        else{
            addEdge(id[u] , id[v] , w_);
            addEdge(id[v] , id[u] , w_);
        }
    }

    int a , b;
    cin >> a >> b;

    depth[id[a]] = w_point[id[a]];
    dfs1(id[a] , 0);

    if(depth[id[b]] == 0) cout << "NO\n";
    else cout << "YES\n";

    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r", stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}