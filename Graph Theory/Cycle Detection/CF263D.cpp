#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 10;

int n , m , k;
vector<int> g[N];

int dfn[N] , fa[N];
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
            while(node != v)
            {
                cycle.push_back(node);
                node = fa[node];
            }
            cycle.push_back(v);

            if((int)cycle.size() > k) return true;
            cycle.clear();
        }
        else if(!dfn[v]){
            if(dfs(v , u)) return true;
        }
    }
    dfn[u] = 2;
    return false;
}

void solve()
{
    cin >> n >> m >> k;
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
                for(int v : cycle) cout << v << " ";
                cout << "\n";
                return;
            }
        }
    }

    cout << "ERROR\n";
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