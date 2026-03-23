#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 10;
int n , m;
vector<int> g[N];

int dfn[N] , timer , fa[N];
vector<int> cycle;

bool dfs(int u , int f)
{
    dfn[u] = 1;
    fa[u] = f;
    for(int v : g[u])
    {
        if(v == f) continue;
        if(dfn[v] == 1)
        {
            int node = u;
            while(node != v){
                cycle.push_back(node);
                node = fa[node];
            }
            cycle.push_back(v);
            cycle.push_back(u);
            return true;
        }
        else if(dfn[v] == 0)
        {
            if(dfs(v , u)) return true;
        }
    }
    dfn[u] = 2;
    return false;
}

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= m ; i++)
    {
        int a , b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int i = 1 ; i <= n ; i++)
    {
        if(!dfn[i]){
            if(dfs(i , 0)){
                cout << (int)cycle.size() << "\n";
                for(auto v : cycle) cout << v << " ";
                return;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r " ,stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}