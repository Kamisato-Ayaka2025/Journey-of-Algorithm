#include <iostream>
#include <vector>

using namespace std;

const int N = 2e3 + 10;

int n;
int depth[N] , parent[N];
bool is_on_diameter[N];
vector<int> g[N];

void dfs_depth(int u , int fa )
{
    parent[u] = fa;
    for(int v : g[u])
    {
        if(v != fa)
        {
            depth[v] = depth[u] + 1;
            dfs_depth(v, u);
        }
    }
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

    int start_node = 1 , max_depth = 0;

    // 求直径
    depth[1] = 0;
    dfs_depth(1 , 0);
    for(int i = 1 ; i <= n ; i++)
    {
        if(depth[i] > max_depth)
        {
            max_depth = depth[i];
            start_node = i;
        }
    }
    int a = start_node;

    depth[a] = 0;
    dfs_depth(a , 0);
    max_depth = 0;
    for(int i = 1 ; i <= n ; i++)
    {
        if(depth[i] > max_depth)
        {
            max_depth = depth[i];
            start_node = i;
        }
    }

    int b = start_node;
    int diameter = depth[b];

    // 标记直径上的点
    int x = a , y = b;
    while(y)
    {
        is_on_diameter[y] = true;
        y = parent[y];
    }

    // 两种情况：直径上有偶数个点或者奇数个点
    if(depth[b] % 2)
    {   // 直径上有偶数个点
        // 先找到中心点
        int mid = a;
        for(int i = 1 ; i <= n ; i++)
        {
            if(i == a || i == b) continue;
            if(is_on_diameter[i] && depth[i] == depth[b] / 2)
            {
                mid = i;
                break;
            }
        }

        cout << diameter / 2 << "\n";
        for(int i = 1 ; i < diameter / 2 ; i++)
        {
            cout << mid << " " << i << "\n";
        }
        cout << mid << " " << 0 << "\n";
    }
    else
    {
        // 中心点有两个
        int c1 = a , c2 = b;
    }
}


int main()
{

}