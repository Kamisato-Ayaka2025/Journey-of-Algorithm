#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int , int> PII;

class Edge{
public:
    int from , to , weight , edgeID , stat;
    Edge(int f , int t , int w , int eid , int state) : from(f) , to(t) , weight(w) , edgeID(eid) , stat(state){};

    inline int theOther(int x){
        return from ^ to ^ x;
    }

    bool operator > (const Edge &W) const{
        return weight > W.weight;
    }

    bool operator < (const Edge &W) const{
        return weight < W.weight;
    }
};

const int N = 1e5 + 10;

int n , m;

vector<int> g[N];
vector<Edge> edge;
vector<Edge> tmp;

vector<PII> g1[N];
int p[N];

int dfn[N] , low[N] , timer;

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

void dfs(int u , int f_eid)
{
    dfn[u] = low[u] = ++timer;
    for(auto t : g1[u])
    {
        int v = t.first;
        int eid = t.second;
        if(eid == f_eid) continue;
        if(!edge[eid].stat) continue; // 表示不考虑这条边

        if(!dfn[v])
        {
            dfs(v , eid);
            low[u] = min(low[u] , low[v]);

            if(low[v] > dfn[u])
            {   // 是Bridge 表示任何一个MST都需要
                edge[eid].stat = 2;
            }
        }
        else
        {
            low[u] = min(low[u] , dfn[v]);
        }
    }


}

void solve()
{
    cin >> n >> m;
    init();
    for(int i = 0 ; i < m ; i++)
    {
        int a ,b , w;
        cin >> a >> b >> w;
        g[a].push_back(i);
        g[b].push_back(i);
        edge.emplace_back(a , b , w , i , 0);
        tmp.emplace_back(a , b , w , i , 0);
    }

    sort(tmp.begin() , tmp.end());
    
    // 筛出None
    for(int i = 0 ; i < m ;  )
    {
        int j = i;
        while(j < m && tmp[j].weight == tmp[i].weight) j++;

        for(int k = i ; k < j ; k++)
        {
            int u = find(tmp[k].from) , v = find(tmp[k].to);
            if(u == v){ // None
                edge[tmp[k].edgeID].stat = 0;
            }
            else{
                edge[tmp[k].edgeID].stat = 1;
                g1[u].push_back({v , tmp[k].edgeID});
                g1[v].push_back({u , tmp[k].edgeID});
            }
        }

        for(int k = i ; k < j ; k++)
        {
            int root = find(tmp[k].from);
            if(!dfn[root]){
                dfs(root , -1);
            }
        }

        for(int k = i ; k < j ; k++)
        {
            int u = tmp[k].from , v = tmp[k].to;
            int pu = find(u) , pv = find(v);
            p[pu] = pv;

            int root1 = find(tmp[k].from);
            dfn[root1] = low[root1] = 0;
            g1[root1].clear();

            int root2 = find(tmp[k].from);
            dfn[root2] = low[root2] = 0;
            g1[root2].clear();
        }
        timer = 0;
        i = j;
    }


    for(int i = 0 ; i < m ; i++)
    {
        if(edge[i].stat == 0){
            cout << "none\n";
        }
        else if(edge[i].stat == 1){
            cout << "at least one\n";
        }
        else{
            cout << "any\n";
        }
    }
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