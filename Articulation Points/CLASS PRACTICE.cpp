#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1e4 + 10;

class Edge{
public:
    int from , to , eid;
    Edge(int f , int t , int id) : from(f) , to(t) , eid(id) { };

    inline int theOther(int x){
        return from ^ to ^ x;
    }
};

int n , m;
vector<int> g[N];
vector<Edge> edge;
int dfn[N] , low[N] , timer;
bool is_cut[N];
vector<int> res;

void dfs(int u , int f_eid)
{
    dfn[u] = low[u] = ++timer;
    int children = 0;
    for(int eid : g[u])
    {
        int v = edge[eid].theOther(u);
        if(v == u) continue; // 自环没影响
        if(eid == f_eid) continue;

        if(!dfn[v])
        {
            dfs(v , eid);
            low[u] = min(low[u] , low[v]);

            if(low[v] >= dfn[u] && f_eid != -1){
                // is_cut
                if(!is_cut[u]){
                    is_cut[u] = true;
                    res.push_back(u);
                }
            }
            children++;
        }
        else
        {
            low[u] = min(low[u] , dfn[v]);
        }
    }

    if(f_eid == -1 && children > 1){
        res.push_back(u);
    }
}

void solve()
{
    cin >> n >> m;
    for(int i = 0 ; i < m ; i++)
    {
        int u , v;
        cin >> u >> v;
        edge.emplace_back(u , v , i);
        g[u].push_back(i);
        g[v].push_back(i);
    }

    for(int i = 1 ; i <= n ; i++){
        if(!dfn[i]) dfs(i , -1);
    }

    sort(res.begin() , res.end());
    cout << (int)res.size() << "\n";
    for(auto v : res){
        cout << v << "\n";
    }
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt"  , "r" , stdin);
    freopen("output.txt"  , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}