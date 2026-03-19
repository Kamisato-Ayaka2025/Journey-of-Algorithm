#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 1e9
typedef long long LL;
typedef pair<int , int> PII;
const int N = 1e3 + 10;
int n , m , k;

int dist[N][N];

class Edge{
public:
    int from , to , weight , edgeID;
    Edge(int f , int t , int w , int eid) : from(f) , to(t) , weight(w) , edgeID(eid) {};
    inline int theOther(int x)
    {
        return from ^ to ^ x;
    }
};

struct Path{
    int start , end;
};

vector<Edge> edge;
vector<int> g[N];
vector<Path> path;

void Dijkstra(int s)
{   // 以s为原点做最短路
    for(int i = 1 ; i <= n ; i++){
        dist[s][i] = INF;
    }

    priority_queue<PII , vector<PII> , greater<PII> > heap;
    dist[s][s] = 0;
    heap.push({dist[s][s] , s});
    while(!heap.empty())
    {
        auto t = heap.top();
        heap.pop();

        int u = t.second;
        for(int eid : g[u])
        {
            int v = edge[eid].theOther(u);
            if(dist[s][v] > dist[s][u] + edge[eid].weight)
            {
                dist[s][v] = dist[s][u] + edge[eid].weight;
                heap.push({dist[s][v] , v});
            }
        }
    }
}



void solve()
{
    cin >> n >> m >> k;
    for(int i = 0 ; i < m ; i++)
    {
        int a , b , c;
        cin >> a >> b >> c;
        edge.emplace_back(a , b , c , i);
        g[a].push_back(i);
        g[b].push_back(i);
    }
    for(int i = 1 ; i <= k ; i++)
    {
        int u , v;
        cin >> u >> v;
        path.push_back({u , v});
    }

    for(int i = 1 ; i <= n ; i++){
        Dijkstra(i);
    }

    LL res = INF;
    for(int i = 0 ; i < m ; i++)
    {
        LL ans = 0ll;
        int c = edge[i].from , d = edge[i].to;
        for(auto p : path)
        {
            int a = p.start , b = p.end;
            ans += min(dist[a][b] , min(dist[a][c] + dist[d][b] , dist[a][d] + dist[c][b]));
        }
        res = min(res , ans);
    }
    cout << res << "\n";
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