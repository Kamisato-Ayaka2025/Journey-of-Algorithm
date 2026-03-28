#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int N = 1e5 + 10 , M = N * 6 + 10;

class Edge{
public:
    int u , v;
};

int n , m;
vector<Edge> edges;

vector<int> g[M];
int dfn[M] , low[M] , timer;
stack<int> stk;
bool in_stk[M];
int id[M] , comp_cnt;

int get_val(int x , int val)
{   // 0代表x为假，1代表x为真
    return 2 * x + val;
}

int get_tree_node(int x)
{   // 线段树上的节点映射到图上
    return 2 * n + 1 + x;
}

// 线段树建树
void build(int idx , int l,  int r)
{   
    if(l == r){
        g[get_tree_node(idx)].push_back(get_val(l , 0));
        return;
    }
    int mid = (l + r) >> 1;
    build(idx << 1 , l , mid);
    build(idx << 1 | 1 , mid + 1 , r);
    g[get_tree_node(idx)].push_back(get_tree_node(idx << 1));
    g[get_tree_node(idx)].push_back(get_tree_node(idx << 1 | 1));
}

// 让from_node到[ql , qr]的节点都为false
void update(int idx , int l , int r , int ql , int qr , int from_node)
{
    if(ql <= l && qr >= r){
        g[from_node].push_back(get_tree_node(idx));
        return;
    }
    int mid = (l + r) >> 1;
    if(ql <= mid) update(idx << 1 , l , mid , ql , qr , from_node);
    if(qr > mid) update(idx << 1 | 1 , mid + 1 , r , ql , qr , from_node);
    return;
}

void dfs(int u)
{
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
        else if(in_stk[v])
        {
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

bool check(int mid)
{
    // clear
    int total_node = get_tree_node(4 * n);
    for(int i = 2 ; i <= total_node ; i++)
    {
        g[i].clear();
        in_stk[i] = false;
        dfn[i] = low[i] = id[i] = 0;
    }

    timer = comp_cnt = 0;
    // 建图
    for(int i = 0 ; i < m ; i++){
        auto e = edges[i];
        int a = e.u , b = e.v;
        g[get_val(a , 0)].push_back(get_val(b , 1));
        g[get_val(b , 0)].push_back(get_val(a , 1));
    }

    build(1 , 1 , n);
    for(int i = 1 ; i <= n ; i++)
    {
        int ql = max(1 , i - mid + 1);
        int qr = min(n , i + mid - 1);

        // 连边
        if(ql <= i - 1) update(1 , 1 , n , ql  ,i - 1 , get_val(i , 1));
        if(qr >= i + 1) update(1 , 1 , n , i + 1 , qr , get_val(i , 1));
    }

    for(int i = 2 ; i <= 2 * n  + 1; i++)
    {
        if(!dfn[i]) dfs(i);
    }

    for(int i = 1 ; i <= n ; i++)
    {
        if(id[get_val(i , 0)] == id[get_val(i , 1)])
        {
            return false;
        }
    }
    return true;
}

void solve()
{
    cin >> n >> m;
    for(int i = 1 ; i <= m ; i++){
        Edge e;
        cin >> e.u >> e.v;
        edges.push_back(e);
    }

    int l = 1 , r = n;
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    cout << r << "\n";
    edges.clear();
    return ;
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

    int T;
    cin >> T;
    while( T-- ){
        solve();
    }
    return 0;
}