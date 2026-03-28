#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int , int> PII;
const int N = 210 , M = N * N;
class Edge{
public:
    Edge(int t , int i) : to(t) , id(i) {};
    int to , id;
};

int n , m;
vector<Edge> g[N];
bool used[M];
int degree[N];
vector<int> odd;
vector<PII> res;

void dfs(int u)
{
    for(auto v : g[u])
    {
        if(used[v.id]) continue;
        used[v.id] = true;

        int ne = v.to;
        if(v.id >= 1 && v.id <= m){
            res.push_back({u , ne});
        }
        dfs(ne);
    }
}

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= m ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].emplace_back(v , i);
        g[v].emplace_back(u , i);
        degree[u]++;
        degree[v]++;
    }

    int ans = 0;
    for(int i = 1 ; i <= n ; i++)
    {   // 奇数度数的点一定成对出现
        if(degree[i] % 2) odd.push_back(i);
        else ans++;
    }

    int edge_count = m + 1;
    for(int i = 0 ; i < (int)odd.size() ; i += 2)
    {
        int u = odd[i] , v = odd[i + 1];
        g[u].emplace_back(v , edge_count);
        g[v].emplace_back(u , edge_count);
        edge_count++;
    }

    for(int i = 1 ; i <= n ; i++) dfs(i);

    cout << ans << "\n";
    for(auto e : res)
    {
        cout << e.first << " " << e.second << "\n";
    }

    //CLEAR
    for(int i = 1 ; i <= n ; i++)
    {
        g[i].clear();
        degree[i] = 0;
    }
    odd.clear();
    res.clear();

    for(int i = 1 ; i <= edge_count ; i++)
    {
        used[i] = false;
    }

    return;
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
    while( T-- )
    {
        solve();
    }
    return 0;
}