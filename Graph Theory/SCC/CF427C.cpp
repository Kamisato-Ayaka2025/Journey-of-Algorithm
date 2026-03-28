#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define INF 0x3f3f3f3f

typedef long long LL;

const int N = 1e5 + 10 , mod = 1000000007;

int n , m;
vector<int> g[N];
int w[N];
int dfn[N] , timestamp , low[N];
int comp_cnt , id[N];

LL cost;
vector<int>min_cnt; // 用来存储每个连通分量里面，最小的weight有多少个

bool in_stk[N];
stack<int> stk;

void dfs(int u) 
{
    dfn[u] = low[u] = ++timestamp;
    stk.push(u);
    in_stk[u] = true;

    for(int v : g[u])
    {
        if(!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(in_stk[v]) 
        {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(low[u] == dfn[u])
    {
        int min_weight = INF;
        int current_scc_min_cnt = 0;

        while(true)
        {
            int node = stk.top();
            stk.pop();
            in_stk[node] = false; 

            id[node] = ++comp_cnt; 

            if(w[node] < min_weight)
            {
                min_weight = w[node];
                current_scc_min_cnt = 1;
            }
            else if(w[node] == min_weight)
            {
                current_scc_min_cnt++;
            }

            if(node == u) break;
        }
        cost += (LL)min_weight;
        min_cnt.push_back(current_scc_min_cnt);
    }
}

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++) cin >> w[i];
    cin >> m;
    for(int i = 1 ; i <= m ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    for(int i = 1 ; i <= n ; i++){
        if(!dfn[i]) dfs(i);
    }

    LL res = 1;
    for(auto v :min_cnt)
    {
        res = (res * v) % mod;
    }

    cout << cost << " " << res << "\n";
    return;
}

// #define _DEBUG
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