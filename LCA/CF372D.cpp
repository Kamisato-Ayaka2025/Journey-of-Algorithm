#include <iostream>
#include <vector>

using namespace std;

#define INF 0x3f3f3f3f
typedef pair<int , int> PII;

const int N = 1e5 + 10;

int n  , k;
vector<int> g[N];
int fa[N] , depth[N] , sz[N] , son[N];
int top[N] , dfn[N] , timestamp , seg[N];

// 重链剖分模版
void dfs1(int u , int f)
{
    fa[u] = f;
    depth[u] = depth[f] + 1;
    sz[u] = 1;
    for(int v : g[u])
    {
        if(v == f) continue;
        dfs1(v , u);
    }

    for(int v :  g[u])
    {
        if(v == f) continue;
        sz[u] += sz[v];
        if(son[u] == 0 || sz[son[u]] < sz[v]){
            son[u] = v;
        }
    }
}

void dfs2(int u , int t)
{
    top[u] = t;
    dfn[u] = ++timestamp;
    seg[timestamp] = u;
    if(son[u] == 0){
        return;
    }
    dfs2(son[u] , t);
    for(int v : g[u])
    {
        if(v != fa[u] && v != son[u]){
            dfs2(v , v);
        }
    }
}

// 重链剖分求LCA
int lca(int a , int b)
{
    while(top[a] != top[b]){
        if(depth[top[a]] <= depth[top[b]]){
            b = fa[top[b]];
        }
        else a = fa[top[a]];
    }
    return depth[a] <= depth[b] ? a : b;
}

// 线段树部分
struct Node{
    int l , r;
    int min_val;
    int min_cnt;
    int lazy_tag;
}tr[N * 4 + 1];

void pushup(int u)
{  
    tr[u].min_val = min(tr[u << 1].min_val , tr[u << 1 | 1].min_val);
    tr[u].min_cnt = 0;
    if(tr[u << 1].min_val == tr[u].min_val) tr[u].min_cnt += tr[u << 1].min_cnt;
    if(tr[u << 1 | 1].min_val == tr[u].min_val) tr[u].min_cnt += tr[u << 1 | 1].min_cnt;
}

void pushdown(int u)
{
    if(tr[u].lazy_tag)
    {
        int lz = tr[u].lazy_tag;
        tr[u << 1].lazy_tag += lz;
        tr[u << 1].min_val += lz;
        tr[u << 1 | 1].lazy_tag += lz;
        tr[u << 1 | 1].min_val += lz;
        tr[u].lazy_tag = 0;
    }
}

void build(int u , int l , int r)
{
    tr[u] = {l , r , 0 , 0 , 0};
    if(l == r)
    {
        tr[u].min_cnt = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1 , l , mid);
    build(u << 1 | 1 , mid + 1 , r);
    pushup(u);
}

void update(int u , int l , int r , int val)
{   // 使l 到 r加上val
    if(tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].lazy_tag += val;
        tr[u].min_val += val;
        return;
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    if(l <= mid) update(u << 1 , l , r , val);
    if(r > mid) update(u << 1 | 1 , l , r , val);
    pushup(u);
}

// 第一个表示min_cnt，第二个表示min_val
// 在这里我们只需要读根节点 所以这个实际上不用写
PII query(int u , int l , int r)
{
    if(tr[u].l >= l && tr[u].r <= r){
        return {tr[u].min_cnt , tr[u].min_val};
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    PII res = {INF , INF};
    if(l <= mid && r > mid){
        PII tmp1 = query(u << 1 , l ,r);
        PII tmp2 = query(u << 1 | 1 , l , r);
        res.second = min(tmp1.second , tmp2.second);
        res.first = 0;
        if(res.second == tmp1.second) res.first += tmp1.first;
        if(res.second == tmp2.second) res.first += tmp2.first;
    }
    else if(l <= mid){
        PII tmp = query(u << 1 , l , r);
        res = tmp;
    }
    else{ // r > mid
        PII tmp = query(u << 1 | 1 , l , r);
        res = tmp;
    }
    pushup(u);
    return res;
}

// 然后利用线段树 + HLD来处理加点和删点操作
void add(int u , int val)
{
    while(u){
        update(1 , dfn[top[u]] , dfn[u] , val);
        u = fa[top[u]];
    }
}

// 然后开一个处理lca的线段树
struct Node_{
    int l , r;
    int lca;
}tr_lca[N * 4 + 1];

void pushup_(int u)
{
    tr_lca[u].lca = lca(tr_lca[u << 1].lca , tr_lca[u << 1 | 1].lca);
}

void build_lca(int u , int l , int r)
{
    tr_lca[u] = {l , r , 0};
    if(l == r){
        tr_lca[u].lca = l;
        return;
    }
    int mid = (l + r) >> 1;
    build_lca(u << 1 , l , mid);
    build_lca(u << 1 | 1 , mid + 1 , r);
    pushup_(u);
}

int query_lca(int u , int l , int r)
{
    if(tr_lca[u].l >= l && tr_lca[u].r <= r)
    {
        return tr_lca[u].lca;
    }

    int mid = (tr_lca[u].l + tr_lca[u].r) >> 1;
    if(l <= mid && r > mid){
        return lca(query_lca(u << 1 , l , r) , query_lca(u << 1 | 1, l  ,r));
    }
    else if(l <= mid){
        return query_lca(u << 1 , l ,r);
    }
    else{
        return query_lca(u << 1 | 1 , l , r);
    }
}

void solve()
{
    cin >> n >> k;
    for(int i = 1 ; i < n ; i++)
    {
        int u ,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 重链剖分初始化
    dfs1(1 , 0);
    dfs2(1 , 1);
    // 线段树初始化
    build(1 , 1 , n);
    build_lca(1 , 1 , n);

    // 双指针过程
    int l = 1 , ans = 0;
    for(int r = 1 ; r <= n ; r++){
        add(r , 1);
        while(l <= r){
            int LCA = query_lca(1 , l,  r);
            int tot_cover = n - (tr[1].min_val == 0 ? tr[1].min_cnt : 0);
            int size = tot_cover - depth[LCA] + 1; // 这里加1是因为我的depth[1] = 1

            if(size > k){
                add(l , -1);
                l++;
            }
            else{
                break;
            }
        }
        ans = max(ans , r - l + 1);
    }

    cout << ans << "\n";
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