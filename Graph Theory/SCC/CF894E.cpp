#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>

using namespace std;

typedef long long LL;

const int N = 1e6 + 10;

class Edge{
public:
    int from , to , weight , edgeID;
    
    Edge(int f , int t , int w , int eid) : from(f) , to(t) , weight(w) , edgeID(eid) {};

    inline int theOther(int x){
        return from ^ to ^ x;
    }
};

int n , m;
vector<int> g[N]; // 存原图
vector<Edge> edge; // 存原边

// Tarjan部分
int dfn[N] , low[N] , timestamp;
bool in_stk[N];
stack<int> stk;

// SCC相关
int comp_cnt , id[N];

// dfs2相关，用于新图的构造
int h[N] , e[N * 2], ne[N * 2], idx , w[N * 2];
LL w_point[N]; // 新图又有点权又有边权 这里是点权
int in[N]; // 表示入度 便于DP
LL dp[N];

LL calc(int x)
{   // 对于一个weight = x计算它的贡献
    LL k = (sqrt(8ll * x  + 1) - 1) / 2;
    return (k + 1) * x - k * (k + 1) * (k + 2) / 6;
}

void addEdge(int u , int v , int c)
{
    e[idx] = v , w[idx] = c , ne[idx] = h[u] , h[u] = idx++;
}

void dfs1(int u)
{   // 对于有向图做Tarjan
    dfn[u] = low[u] = ++timestamp;
    in_stk[u] = true;
    stk.push(u);

    for(int eid : g[u])
    {
        int v = edge[eid].theOther(u);
        if(!dfn[v])
        {
            dfs1(v);
            low[u] = min(low[u] , low[v]);
        }
        else if(in_stk[v])
        {
            low[u] = min(low[u] , dfn[v]);
        }
    }

    if(low[u] == dfn[u])
    {
        comp_cnt++;
        while(true)
        {
            int node = stk.top();
            stk.pop();

            in_stk[node] = false;
            id[node] = comp_cnt;

            if(node == u) break;
        }
    }
} 

void solve()
{
    memset(h , -1 , sizeof h);
    cin >> n >> m;
    for(int i = 0 ; i < m ; i++)
    {
        int u , v , w;
        cin >> u >> v >> w;
        edge.emplace_back(u , v , w , i);
        g[u].push_back(i);
    }

    // Tarjan先预处理连通分量
    for(int i = 1 ; i <= n ; i++)
    {
        if(!dfn[i]) dfs1(i);
    }

    // 构建新图
    for(auto e : edge)
    {
        int u = e.from , v = e.to;
        if(id[u] == id[v]){
            w_point[id[u]] += calc(e.weight);
        }
        else{
            addEdge(id[u] , id[v] , e.weight);
            in[id[v]]++;
        }
    }

    // 在新图上做DP求最长路
    int s;
    cin >> s;
    queue<int> q;
   
    for(int i = 1 ; i <= comp_cnt ; i++)
    {
        if(!in[i]) q.push(i);
        dp[i] = -1;
    }

    dp[id[s]] = w_point[id[s]];

    while(!q.empty())
    {
        int t = q.front();
        q.pop();

        for(int i = h[t] ; ~i ; i = ne[i])
        {
            int j = e[i];
            if(dp[t] != -1){
                dp[j] = max(dp[j] , dp[t] + w[i] + w_point[j]);
            }
            in[j]--;
            if(!in[j]){
                q.push(j);
            }
        }
    }


    LL res = 0;
    for(int i = 1 ; i <= comp_cnt ; i++){
        res = max(res , dp[i]);
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

    solve();
    return 0;
}