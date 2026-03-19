#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 1e18
const int N = 1e5 + 10;
typedef long long LL;
typedef pair<LL , int> PII;

class Edge{
public:
    int from , to , weight , edgeID;
    bool pass = false;
    int cost = 0;
    Edge(int f , int t , int w , int eid) : from(f) , to(t) , weight(w) , edgeID(eid) {};
    inline int theOther(int x){
        return from ^ to ^ x;
    }
    bool operator > (const Edge &W) const{
        return weight > W.weight;
    }
};

int n , m , s , t;
vector<int> g[N];
vector<Edge> edge;

vector<int> g1[N];
vector<int> g2[N];
vector<Edge> edge1;

LL distS[N] , distT[N];

int dfn[N] , low[N] , timer;

void Dijkstra()
{
    for(int i = 1 ; i <= n ; i++){
        distS[i] = INF;
        distT[i] = INF;
    }

    priority_queue<PII, vector<PII> , greater<PII> > heap;
    distS[s] = 0ll;
    heap.push({distS[s] , s});

    while(!heap.empty())
    {
        auto t = heap.top();
        heap.pop();

        int u = t.second;
        for(auto eid : g[u])
        {
            int v = edge[eid].theOther(u);
            if(distS[v] > distS[u] + edge[eid].weight)
            {
                distS[v] = distS[u] + edge[eid].weight;
                heap.push({distS[v] , v});
            }
        }
    }

    // 在反向图上跑
    distT[t] = 0ll;
    heap.push({distT[t] , t});
    while(!heap.empty())
    {
        auto t = heap.top();
        heap.pop();

        int u = t.second;
        for(auto eid : g2[u])
        {
            int v = edge[eid].theOther(u);
            if(distT[v] > distT[u] + edge[eid].weight)
            {
                distT[v] = distT[u] + edge[eid].weight;
                heap.push({distT[v] , v});
            }
        }
    }
}

void build_new_graph()
{
    int idx = 0;
    for(auto e : edge)
    {
        int u = e.from , v = e.to , w = e.weight;
        if(distS[u] + distT[v] + w == distS[t])
        {
            edge1.push_back(e);
            // Tarjan要在无向图上跑
            g1[u].push_back(idx);
            g1[v].push_back(idx);
            idx++;
        }
    }
}

void Tarjan(int u , int f_eid)
{
    dfn[u] = low[u] = ++timer;
    for(int eid : g1[u])
    {
        if(eid == f_eid) continue;
        int v = edge1[eid].theOther(u);
        if(!dfn[v])
        {
            Tarjan(v , eid);
            low[u] = min(low[u] , low[v]);
            if(low[v] > dfn[u])
            {   // is_bridge
                edge[edge1[eid].edgeID].pass = true;
            }
        }
        else
        {
            low[u] = min(low[u] , dfn[v]);
        }
    }
}

void Try_Repair()
{   // 然后尝试将那些不是Bridge的边进行修复
    LL D = distS[t];
    for(auto &e : edge)
    {
        int u = e.from , v = e.to;
        if(D - 1 - distS[u] - distT[v] >= 1)
        {
            e.cost = e.weight - D + 1 + distS[u] + distT[v];
        }
    }
}

void solve()
{
    cin >> n >> m >> s >> t;
    for(int i = 0 ; i < m ; i++)
    {
        int u , v , c;
        cin >> u >> v >> c;
        edge.emplace_back(u , v , c , i);
        g[u].push_back(i);
        g2[v].push_back(i); // 反向图
    }

    Dijkstra();
    build_new_graph();
    Tarjan(s , -1);
    Try_Repair();

    // OutPut
    for(auto e : edge)
    {
        if(e.pass){
            cout << "YES\n";
        }
        else if(e.cost > 0)
        {   // 等于0不就是必须经过？
            cout << "CAN ";
            cout << e.cost << "\n";
        }
        else{
            cout << "NO\n";
        }
    }
    return;
}

//#define _DEBUG
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