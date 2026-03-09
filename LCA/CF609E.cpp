#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;
int n , m;
int up[N][20] , depth[N] , max_e[N][20];
bool st[N];
LL sum;

class Edge{
public:
    int from , to , weight , edgeID;
    Edge(int f ,int t ,int w,int eid) : from(f) , to(t) , weight(w) , edgeID(eid) {}; 
    
    inline int theOther(int x){
        return from ^ to ^ x;
    }

    bool operator < (const Edge &W) const{
        return weight < W.weight;
    }
};

int p[N];
vector<int> g[N] , g1[N]; // g1存生成树
vector<Edge> edge;

void init()
{
    for(int i = 1 ; i <= n ; i++){
        p[i] = i;
    }
}

int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void dfs(int u , int f , int fid)
{
    max_e[u][0] = (f == 0 ? -1 : edge[fid].weight); // 防止根节点

    up[u][0] = f;
    for(int j = 1 ; j < 20 ; j++){
        up[u][j] = up[up[u][j - 1]][j - 1];
        max_e[u][j] = max(max_e[u][j - 1] , max_e[up[u][j - 1]][j - 1]);
    }

    for(int eid : g1[u])
    {
        int v = edge[eid].theOther(u);
        if(v == f) continue;
        depth[v] = depth[u] + 1;
        dfs(v , u , eid);
    }
}

int kth(int u , int k)
{
    int res = -1;
    for(int j = 19 ; j >= 0 ; j--){
        if(k & (1 << j)){
            res = max(res , max_e[u][j]);
            u = up[u][j];
        }
    }
    return res;
}

void solve()
{
    cin >> n >> m;
    init();

    priority_queue<Edge , vector<Edge> , greater<Edge>> pq;

    for(int i = 0 ; i < m ; i++)
    {
        int u , v , w;
        cin >> u >> v >> w;
        edge.emplace_back(u , v , w , i);
        pq.push(edge[i]);
        g[u].push_back(i);
        g[v].push_back(i);
    }

    // MST
    for(int i = 0 ; i < m ; i++)
    {
        auto t = pq.top();
        pq.pop();

        int a = t.from , b = t.to;
        int pa = find(a) , pb = find(b);
        if(pa != pb)
        {
            int idx = t.edgeID;
            sum += t.weight;
            g1[a].push_back(idx);
            g1[b].push_back(idx);
            p[pa] = pb;
            st[idx] = true;
        }
    }

    // Query
    dfs(1 , 0 , 0);
    for(int i = 0 ; i < m ; i++)
    {
        if(st[i]){
            // spanning edge
            cout << sum << "\n";
        }
        else{// back_edge
            int u = edge[i].from , v = edge[i].to;
            if(depth[u] < depth[v]) swap(u , v);

            int dist = depth[u] - depth[v];
            cout << sum + edge[i].weight - kth(u , dist) << "\n";
        }
    }
    return;
}

#define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt"  ,"r" , stdin);
    freopen("output.txt"  ,"w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}