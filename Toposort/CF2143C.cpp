#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

int n;
int in[N] , q[N] , tt , hh;
int res[N];
vector<int> g[N];

void toposort()
{
    for(int i = 1 ; i <= n ; i++)
    {
        if(!in[i]) q[++tt] = i;
    }

    while(hh <= tt)
    {
        int node = q[hh++];
        for(auto v : g[node])
        {
            in[v]--;
            if(!in[v]){
                q[++tt] = v;
            }
        }
    }
}

void solve()
{
    // init
    hh = 0 , tt = -1;
    for(int i = 1 ; i <= n ; i++){
        in[i] = 0;
        g[i].clear();
    }


    cin >> n;
    for(int i = 1 ; i < n ; i++)
    {
        int u , v , x , y;
        cin >> u >> v >> x >> y;
        if(u > v) swap(u , v);

        if(x > y)
        {
            g[v].push_back(u);
            in[u]++;
        }
        else {
            g[u].push_back(v);
            in[v]++;
        }
    }

    toposort();

    for(int i = 0 ; i < n ; i++)
    {
        res[q[i]] = i + 1;
    }

    for(int i = 1 ; i <= n ; i++){
        cout << res[i] << " ";
    }
    cout << "\n";
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

    int T;
    cin >> T;
    while(T--)solve();
    return 0;
}