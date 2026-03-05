#include <iostream>
#include <vector>

using namespace std;

const int N = 5e5 + 10;

class Edge{
public:
    int from , to , edgeID;
    Edge(int from , int to , int edgeID) : from(from) , to(to) , edgeID(edgeID) {}

    inline int theOther(int x)
    {
        return from ^ to ^ x;
    }
};

int n;
int col[N] , _depth[N];
int dfn[N][2], timer1 , timer2 ;
int bel[N][2] , sz[N][2];
// dfn表示以a和b为根的树的时间戳，sz表示以a和b为根的树的子树大小
// 通过dfn我们将节点映射到线段树上，sz则是为了快速找到区间边界
int depth[N][2] , col_prefix[N][2];
vector<int> g[N];
vector<Edge> edges;



void dfs_depth(int u , int fa)
{
    for(int i : g[u])
    {
        int v = edges[i].theOther(u);
        if(v == fa) continue;
        _depth[v] = _depth[u] + 1;
        dfs_depth(v , u);
    }
}

void dfs_mark(int u,  int fa , int ver , int &timer)
{   // ver表示是第几棵树
    dfn[u][ver] = ++timer;
    bel[timer][ver] = u;
    sz[u][ver] = 1;

    for(int i : g[u])
    {
        int v = edges[i].theOther(u);
        if(v == fa) continue;
        depth[v][ver] = depth[u][ver] + 1;

        // 处理颜色
        // 我们是将每个树上的 更深节点 当成这条边的索引
        col_prefix[v][ver] = col[i];
        col_prefix[v][ver] ^= col_prefix[u][ver];

        dfs_mark(v , u , ver , timer);
        sz[u][ver] += sz[v][ver];
    }
}

// 线段树部分
struct Node{
    int l , r;
    int lazy_tag;
    int max_depth[2]; // 当前区间内，奇偶性为0和1的最大深度
}tr[N * 4 + 1][2];

void pushup(int u , int ver)
{
    tr[u][ver].max_depth[0] = max(tr[u << 1][ver].max_depth[0] , tr[u << 1 | 1][ver].max_depth[0]);
    tr[u][ver].max_depth[1] = max(tr[u << 1][ver].max_depth[1] , tr[u << 1 | 1][ver].max_depth[1]);
}

void pushdown(int u , int ver)
{
    if(tr[u][ver].lazy_tag)
    {
        swap(tr[u << 1][ver].max_depth[0], tr[u << 1][ver].max_depth[1]);
        tr[u << 1][ver].lazy_tag ^= 1;

        swap(tr[u << 1 | 1][ver].max_depth[0], tr[u << 1 | 1][ver].max_depth[1]);
        tr[u << 1 | 1][ver].lazy_tag ^= 1;
        tr[u][ver].lazy_tag = 0;
    }
}

void build(int u , int l , int r , int ver)
{   // ver来表示是以a为根还是以b为根
    tr[u][ver] = {l , r , 0 , 0 , 0};
    
    if(l == r){
        int node_on_realTree = bel[l][ver];
        tr[u][ver].max_depth[col_prefix[node_on_realTree][ver]] = depth[node_on_realTree][ver];
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1 , l , mid , ver );
    build(u << 1 | 1,  mid + 1 , r , ver);
    pushup(u , ver);
}

void inverse(int u , int l , int r , int ver)
{   // 区间翻转
    if(tr[u][ver].l >= l && tr[u][ver].r <= r)
    {
        swap(tr[u][ver].max_depth[0] , tr[u][ver].max_depth[1]);
        tr[u][ver].lazy_tag ^= 1;
        return;
    }
    pushdown(u , ver);
    int mid = (tr[u][ver].l + tr[u][ver].r) >> 1;
    if(l <= mid) inverse(u << 1, l , r , ver);
    if(r > mid) inverse(u << 1 | 1,  l , r ,ver);
    pushup(u , ver);
    return;
}

int query(int u , int l , int r , int ver)
{   // 查询区间内最深的且为0的值
    if(tr[u][ver].l >= l && tr[u][ver].r <= r)
    {
        return tr[u][ver].max_depth[0];
    }
    pushdown(u , ver);
    int mid = (tr[u][ver].l + tr[u][ver].r) >> 1;
    int res = 0;
    if(l <= mid) res = max(res , query(u << 1 , l , r , ver));
    if(r > mid) res = max(res , query(u << 1 | 1 , l ,r , ver));
    pushup(u , ver);
    return res;
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
        if(_depth[i] > maxd)
        {
            maxd = _depth[i];
            maxid = i;
        }
    }
    int a = maxid;

    maxd = 0;
    _depth[a] = 0;
    dfs_depth(a , 0);
    for(int i = 1; i <= n; i++)
    {
        if(_depth[i] > maxd)
        {
            maxd = _depth[i];
            maxid = i;
        }
    }
    int b = maxid;

    // 然后分别以两个直径为根 构建新树
    // 并且打上时间戳 准备线段树操作
    dfs_mark(a , 0 , 0 , timer1);
    dfs_mark(b , 0 , 1 , timer2);

    build(1 , 1 , n , 0);
    build(1 , 1 , n , 1);

    int q;
    cin >> q;
    while( q-- )
    {
        int id;
        cin >> id;
        auto e = edges[id - 1];
        int u = e.from , v = e.to;

        // 先考虑第一棵树
        int res = 0;
        for(int i = 0 ; i < 2 ; i++)
        {
            int node = (depth[u][i] > depth[v][i] ? u : v);
            inverse(1 , dfn[node][i] , dfn[node][i] + sz[node][i] - 1 , i);
            res = max(res , query(1 , 1 , n , i));
        }
        cout << res << "\n";
    }
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt"  , "r" , stdin);
    freopen("output.txt" , "w" , stdout); 
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}