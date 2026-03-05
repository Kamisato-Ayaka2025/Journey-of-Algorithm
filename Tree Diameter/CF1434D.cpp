#include <iostream>
#include <vector>

using namespace std;

const int N = 5e5 + 10;

int n;
int col[N] , depth[N];
int dfn1[N] , dfn2[N] , timer1 , timer2 , sz1[N] , sz2[N];
// dfn表示以a和b为根的树的时间戳，sz表示以a和b为根的树的子树大小
// 通过dfn我们将节点映射到线段树上，sz则是为了快速找到区间边界
vector<int> g[N];
vector<Edge> edges;

class Edge{
    int from , to , edgeID;
    Edge(int from , int to , int edgeID) : from(from) , to(to) , edgeID(edgeID) {}

    inline int theOther(int x)
    {
        return from ^ to ^ x;
    }
};

void dfs_depth(int u , int fa)
{
    for(int i : g[u])
    {
        int v = edges[i].theOther(u);
        if(v == fa) continue;
        depth[v] = depth[u] + 1;
        dfs_depth(v , u);
    }
}

void dfs_mark(int u,  int fa , int *dfn , int &timer , int *sz)
{
    dfn[u] = ++timer;
    sz[u] = 1;

    for(int i : g[u])
    {
        int v = edges[i].theOther(u);
        if(v == fa) continue;
        dfs_mark(v , u , dfn , timer , sz);
        sz[u] += sz[v];
    }
}

// 线段树部分
struct Node{
    int l , r;
    int lazy_tag;
    int max_depth[2]; // 当前区间内，奇偶性为0和1的最大深度
}tr[N * 4 + 1][2];

void pushup(int u)
{
    for(int i = 0; i < 2; i++)
    {
        tr[u][i].max_depth[0] = max(tr[u << 1][i].max_depth[0] , tr[u << 1 | 1][i].max_depth[0]);
        tr[u][i].max_depth[1] = max(tr[u << 1][i].max_depth[1] , tr[u << 1 | 1][i].max_depth[1]);
    }
}

void pushdown(int u)
{
    if(tr[u][0].lazy_tag)
    {
        for(int i = 0; i < 2; i++)
        {
            swap(tr[u << 1][i].max_depth[0] , tr[u << 1][i].max_depth[1]);
            swap(tr[u << 1 | 1][i].max_depth[0] , tr[u << 1 | 1][i].max_depth[1]);
            tr[u << 1][i].lazy_tag ^= 1;
            tr[u << 1 | 1][i].lazy_tag ^= 1;
        }
        tr[u][0].lazy_tag = 0;
    }
}



void update(int u , int l , int r)
{   // 同时翻转两棵树

}

void solve()
{
    cin >> n;
    for(int i = 0 ; i < n - 1; i++)
    {
        int u , v , t;
        cin >> u >> v >> t;
        g[u].push_back(i);
        g[v].push_back(i);
        edges.emplace_back(u , v , t);
        col[i] = t;
    }

    // 首先获取直径
    int maxd = 0 , maxid = 1;
    dfs_depth(1 , 0);
    for(int i = 1; i <= n; i++)
    {
        if(depth[i] > maxd)
        {
            maxd = depth[i];
            maxid = i;
        }
    }
    int a = maxid;

    maxd = 0;
    depth[a] = 0;
    dfs_depth(a , 0);
    for(int i = 1; i <= n; i++)
    {
        if(depth[i] > maxd)
        {
            maxd = depth[i];
            maxid = i;
        }
    }
    int b = maxid;

    // 然后分别以两个直径为根 构建新树
    // 并且打上时间戳 准备线段树操作
    dfs_mark(a , 0 , dfn1 , timer1 , sz1);
    dfs_mark(b , 0 , dfn2 , timer2 , sz2);


}

int main()
{

}