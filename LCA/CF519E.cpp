#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 10;
int n;
vector<int> g[N];
int depth[N] , up[N][20] , sz[N];

void dfs(int u , int f)
{
    sz[u] = 1;

    up[u][0] = f;
    for(int i = 1 ; i < 20 ; i++){
        up[u][i] = up[up[u][i - 1]][i - 1];
    }

    for(int v : g[u])
    {
        if(v == f) continue;
        depth[v] = depth[u] + 1;
        dfs(v , u);
        sz[u] += sz[v];
    }
}

int lca(int a , int b)
{
    if(depth[a] < depth[b]) swap(a , b);

    int f = depth[a] - depth[b];
    for(int j = 19 ; j >= 0 ; j--)
    {
        if(f & (1 << j)){
            a = up[a][j];
        }
    }

    if(a == b) return a;

    for(int j = 19 ; j >= 0 ; j--){
        if(up[a][j] != up[b][j]){
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

int kth(int u , int k)
{
    for(int j = 19 ; j >= 0 ; j--){
        if(k & (1 << j)){
            u = up[u][j];
        }
    }
    return u;
}

void solve()
{
    cin >> n;
    for(int i = 1 ; i < n ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1 , 0);
    int q;
    cin >> q;

    while( q-- )
    {
        int x , y;
        cin >> x >> y;
        if(x == y){
            cout << n << "\n";
            continue;
        }
        int z = lca(x , y);
        int len = depth[x] + depth[y] - 2 * depth[z];
        if(len % 2){
            cout << 0 << "\n";
            continue;
        }
        else{
            int steps = len / 2;
            // 分两种情况：
            if(depth[x] - depth[z] == depth[y] - depth[z]){
                int son_to_x = kth(x , steps - 1);
                int son_to_y = kth(y , steps - 1);
                cout << (n - sz[son_to_x] - sz[son_to_y]) << "\n";
            }
            else{
                if(depth[x] < depth[y]) swap(x , y);
                int son_to_x = kth(x , steps - 1);
                int mid = kth(x , steps);
                cout << sz[mid] - sz[son_to_x] << "\n";
            }
        }
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

    solve();
    return 0;
}