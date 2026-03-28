#include <iostream>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

int n , m , k;
vector<int> g[N];
vector<int> order;
bool vis[N];

void dfs(int u)
{
    vis[u] = true;
    order.push_back(u);

    for(int v : g[u])
    {
        if(vis[v]) continue;
        dfs(v);
        if(order.back() != u) order.push_back(u);
    }
}

void solve()
{
    cin >> n >> m >> k;
    
    for(int i = 1 ; i <= m ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);

    int cnt = (((int)order.size()) + k - 1) / k;
    int num = 0;

    vector<int> ans;
    for(int i = 0 ; i < (int)order.size() ; i++)
    {
        ans.push_back(order[i]);
        if(i == (int)order.size() - 1 || (int)ans.size() == cnt)
        {
            cout << ans.size() << " ";
            for(int v : ans) cout << v << " ";
            cout << "\n";
            ans.clear();
            num++;
        }
    }

    while(num < k)
    {
        cout << "1 1\n";
        num++;
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