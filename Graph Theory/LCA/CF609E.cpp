#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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

    bool operator > (const Edge &W) const{
        return weight > W.weight; 
    }
};

int p[N];
vector<int> g1[N]; 
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

void dfs(int u , int f , int w)
{
    depth[u] = depth[f] + 1;
    up[u][0] = f;
    max_e[u][0] = w; 

    for(int j = 1 ; j < 20 ; j++){
        up[u][j] = up[up[u][j - 1]][j - 1];
        max_e[u][j] = max(max_e[u][j - 1] , max_e[up[u][j - 1]][j - 1]);
    }

    for(int eid : g1[u])
    {
        int v = edge[eid].theOther(u);
        if(v == f) continue;
        dfs(v , u , edge[eid].weight);
    }
}

int get_path_max(int u, int v)
{
    if(depth[u] < depth[v]) swap(u, v);
    int res = 0;

    for(int j = 19; j >= 0; j--){
        if(depth[up[u][j]] >= depth[v]){
            res = max(res, max_e[u][j]);
            u = up[u][j];
        }
    }

    if(u == v) return res;

    for(int j = 19; j >= 0; j--){
        if(up[u][j] != up[v][j]){
            res = max(res, max(max_e[u][j], max_e[v][j]));
            u = up[u][j];
            v = up[v][j];
        }
    }

    return max(res, max(max_e[u][0], max_e[v][0]));
}

void solve()
{
    if (!(cin >> n >> m)) return;
    init();

    priority_queue<Edge , vector<Edge> , greater<Edge>> pq;

    for(int i = 0 ; i < m ; i++)
    {
        int u , v , w;
        cin >> u >> v >> w;
        edge.emplace_back(u , v , w , i);
        pq.push(edge[i]);
    }

    // MST
    int cnt = 0;
    while(!pq.empty() && cnt < n - 1)
    {
        auto t = pq.top();
        pq.pop();

        int a = t.from , b = t.to;
        int pa = find(a) , pb = find(b);
        if(pa != pb)
        {
            int idx = t.edgeID;
            sum += (LL)t.weight;
            g1[a].push_back(idx);
            g1[b].push_back(idx);
            p[pa] = pb;
            st[idx] = true;
            cnt++;
        }
    }

    dfs(1 , 0 , 0);

    // 求解
    for(int i = 0 ; i < m ; i++)
    {
        if(st[i]){
            cout << sum << "\n";
        }
        else{
            int u = edge[i].from , v = edge[i].to;
            cout << sum + (LL)edge[i].weight - (LL)get_path_max(u , v) << "\n";
        }
    }
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt"  ,"r" , stdin);
    freopen("output.txt " ,"w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}