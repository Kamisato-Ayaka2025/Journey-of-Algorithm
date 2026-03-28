#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#define INF 0x3f3f3f3f

const int N = 2e5 + 10;

class Edge{
public:
    int from , to , eid;
    Edge(int f , int t , int eid) : from(f) , to(t) , eid(eid) {};

    inline int theOther(int x){
        return from ^ to ^ x;
    }
};

int n , m;
vector<int> g[N];
vector<Edge> edge;

int dfn[N] , timer , low[N];
int comp_cnt , id[N];

stack<int> stk;

int dist[N] , rep[N];
bool in_queue[N];

void dfs(int u , int f)
{
    dfn[u] = low[u] = ++timer;
    stk.push(u);

    for(int eid : g[u])
    {
        int v = edge[eid].theOther(u);
        if(v == f) continue;

        if(!dfn[v])
        {   
            dfs(v , u);
            low[u] = min(low[u] , low[v]);
        }
        else
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

            id[node] = comp_cnt;
            if(node == u) break;
        }
    }
}

vector<pair<int, int>> tree_g[N]; 

// 用来在缩点树上找1 ~ n的最短路径
bool find_path(int u, int target, int p_id) {
    if (u == target) return true;
    for (auto& out : tree_g[u]) {
        int v = out.first;
        int eid = out.second;
        if (v == p_id) continue;

        if (find_path(v, target, u)) {
            int u_orig = edge[eid].from;
            int v_orig = edge[eid].to;
            
            for (int node : {u_orig, v_orig}) {
                dist[node] = 0;
                rep[node] = min(rep[node], eid + 1); 
            }
            return true;
        }
    }
    return false;
}

void init()
{
    for(int i = 1 ; i <= n ; i++){
        g[i].clear();
        dist[i] = INF;
        in_queue[i] = 0;
        dfn[i] = low[i] = 0;
        id[i] = 0;
        rep[i] = INF;
        tree_g[i].clear();
    }
    timer = comp_cnt = 0;
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

    // 准备BFS
    queue<int> q;

    for(int i = 0; i < m; i++) {
        int u = edge[i].from, v = edge[i].to;
        if(id[u] != id[v]) {
            tree_g[id[u]].push_back({id[v], i});
            tree_g[id[v]].push_back({id[u], i});
        }
    }

    find_path(id[1], id[n], -1);
    
    for(int i = 1 ; i <= n ; i++) if(!dist[i]) q.push(i);

    for(int i = 1 ; i <= n ; i++)
    {
        if(!dist[i]) q.push(i);
    }

    //BFS
    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int eid : g[u])
        {
            int v = edge[eid].theOther(u);
            if(dist[v] > dist[u] + 1)
            {
                dist[v] = dist[u] + 1;
                rep[v] = rep[u];
                q.push(v);
            }
            else if(dist[v] == dist[u] + 1)
            {
                rep[v] = min(rep[v] , rep[u]);
            }
        }
    }

    int Q;
    cin >> Q;
    while( Q-- )
    {
        int a;
        cin >> a;
        cout << (dist[a] == INF ? -1 : rep[a]) << " ";
    }
    cout << "\n";
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
    while( T-- ) solve();
    return 0;
}