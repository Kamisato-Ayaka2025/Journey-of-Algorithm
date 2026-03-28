#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int N = 1e5 + 10 , M = 2 * N + 10;

int n , m;
int d[N];
vector<int> control[N];
vector<int> g[M];

int dfn[M] , low[M] , timer;
stack<int> stk;
bool in_stk[M];
int id[M] , comp_cnt;

void addEdge_Same(int a , int b)
{
    int x1 = a * 2 , x2 = a * 2 + 1;
    int y1 = b * 2 , y2 = b * 2 + 1;
    g[x1].push_back(y1);
    g[y1].push_back(x1);
    g[x2].push_back(y2);
    g[y2].push_back(x2);
}

void addEdge_Diff(int a , int b)
{
    int x1 = a * 2 , x2 = a * 2 + 1;
    int y1 = b * 2 , y2 = b * 2 + 1;
    g[x1].push_back(y2);
    g[y2].push_back(x1);
    g[x2].push_back(y1);
    g[y1].push_back(x2);
}

void dfs(int u)
{ // On a directed graph
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    in_stk[u] = true;
    for(int v : g[u])
    {
        if(!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u] , low[v]);
        }
        else if(in_stk[v]){
            low[u] = min(low[u] , dfn[v]);
        }
    }

    if(dfn[u] == low[u])
    {
        comp_cnt++;
        while(true)
        {
            int node = stk.top();
            stk.pop();
            in_stk[node] = false;

            id[node] = comp_cnt;
            if(node == u) break;
        }
    }
}

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++){
        cin >> d[i];
        d[i] ^= 1;
    }

    for(int i = 1 ; i <= m ; i++){
        int k;
        cin >> k;
        while( k-- )
        {
            int x;
            cin >> x;
            control[x].push_back(i);
        }
    }

    // Build-Graph
    for(int i = 1 ; i <= n ; i++)
    {
        int u = control[i][0] , v = control[i][1];
        if(d[i]) addEdge_Diff(u , v);
        else addEdge_Same(u , v);
    }

    // Tarjan
    for(int i = 2 ; i <= m * 2 ; i++)
    {
        if(!dfn[i]) dfs(i);
    }

    for(int i = 1 ; i <= m ; i++)
    {
        if(id[i * 2] == id[i * 2 + 1]){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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