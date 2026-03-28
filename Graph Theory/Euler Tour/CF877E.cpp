#include <iostream>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

int n;
vector<int> g[N];
int dfn[N] , bel[N] , sz[N] , timer;
int turn[N];

// 构建DFS序
void dfs(int u)
{
    sz[u] = 1;
    dfn[u] = ++timer;
    bel[timer] = u;

    for(int v : g[u])
    {
        dfs(v);
        sz[u] += sz[v];
    }
}

// 线段树
struct Node{
    int l , r;
    int sum;
    int lazy_tag;
}tr[N * 4 + 1];

void pushup(int u)
{
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum);
}

void pushdown(int u)
{
    if(tr[u].lazy_tag)
    {
        tr[u << 1].sum = (tr[u << 1].r - tr[u << 1].l + 1) - tr[u << 1].sum;
        tr[u << 1 | 1].sum = (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) - tr[u << 1 | 1].sum;

        tr[u << 1].lazy_tag ^= 1;
        tr[u << 1 | 1].lazy_tag ^= 1;

        tr[u].lazy_tag = 0;
    }
}

void build(int u , int l , int r)
{
   tr[u] = {l , r , 0 , 0}; 
   if(l == r)
   {
       int node = bel[l];
       tr[u].sum = turn[node];
       return;
   }

   int mid = (l + r) >> 1;
   build(u << 1 , l , mid);
   build(u << 1 | 1 , mid + 1 , r);
   pushup(u);
}

void inverse(int u , int l , int r)
{
    if(tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].sum = (tr[u].r - tr[u].l + 1) - tr[u].sum;
        tr[u].lazy_tag ^= 1;
        return;
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    if(l <= mid) inverse(u << 1 , l , r);
    if(r > mid) inverse(u << 1 | 1 , l , r);
    pushup(u);
}

int query(int u , int l , int r)
{
    if(tr[u].l >= l && tr[u].r <= r)
    {
        return tr[u].sum;
    }

    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1 , res = 0;
    if(l <= mid) res += query(u << 1 , l , r);
    if(r > mid) res += query(u << 1 | 1 , l , r);
    pushup(u);
    return res;
}

void solve()
{
    cin >> n;
    for(int i = 2 ; i <= n ; i++)
    {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    for(int i = 1 ; i <= n ; i++)
    {
        cin >> turn[i];
    }

    dfs(1);
    build(1 , 1 , n);

    int q;
    cin >> q;
    while( q-- )
    {   
        int u;
        char op[4];
        cin >> op >> u;
        if(op[0] == 'g')
        {
            cout << query(1 , dfn[u] , dfn[u] + sz[u] - 1) << "\n";
        }
        else
        {
            inverse(1 , dfn[u] , dfn[u] + sz[u] - 1);
        }
    }   
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