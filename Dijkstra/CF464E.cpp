#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int N = 1e5 + 10 , MAX_BIT = 1e5 + 10;
const int M = MAX_BIT + 100 , mod = 1e9 + 7; // 要预留进位

typedef long long LL;
typedef unsigned long long ULL;
const ULL BASE = 13331;
ULL pw2[M] , pw_base[M];

// 初始化哈希
void init_hash()
{
    pw2[0] = 1ull;
    pw_base[0] = 1ull;
    for(int i = 1 ; i < M ; i++){
        pw2[i] = (pw2[i - 1] * 2) % mod;
        pw_base[i] = pw_base[i - 1] * BASE;
    }
}

// PST
int idx;

struct{
    int left , right;
    ULL h;
}tr[N * 120];

void pushup(int u , int l , int r)
{
    int mid = (l + r) >> 1;
    tr[u].h =tr[tr[u].left].h + pw_base[mid - l + 1] * tr[tr[u].right].h;
}

int build(int l , int r)
{
    int u = ++idx;
    if(l == r) return u;
    int mid = (l + r) >> 1;
    tr[u].left = build(l , mid);
    tr[u].right = build(mid + 1,  r);
    return u;
}

int update_one(int old , int l , int r , int pos)
{
    int u = ++idx;
    tr[u] = tr[old];
    if(l == r){
        tr[u].h = 1;
        return u;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) tr[u].left = update_one(tr[old].left , l , mid , pos);
    else tr[u].right = update_one(tr[old].right , mid + 1 , r , pos);
    pushup(u , l , r);
    return u;
}

// 区间赋值为0
int update_zero(int old , int zero_root , int l , int r , int ql , int qr)
{
    if(ql <= l && qr >= r){
        return zero_root;
    }
    int u = ++idx;
    tr[u] = tr[old];
    int mid = (l + r) >> 1;
    if(ql <= mid){
        tr[u].left = update_zero(tr[old].left , tr[zero_root].left , l , mid , ql , qr);
    }
    if(qr > mid){
        tr[u].right = update_zero(tr[old].right , tr[zero_root].right , mid + 1 , r , ql , qr);
    }
    pushup(u , l , r);
    return u;
}

// 构建一棵全1树
ULL full[N * 4];
void init_full_hash(int u , int l , int r)
{
    if(l == r){
        full[u] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    init_full_hash(u << 1,  l,  mid);
    init_full_hash(u << 1 | 1 , mid + 1 , r);
    full[u] = full[u << 1] + pw_base[mid - l + 1] * full[u << 1 | 1];
}

// 找第一个0
int find_first_zero(int u , int l , int r , int ql , int node_full)
{
    if(tr[u].h == full[node_full]) return -1;
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(ql <= mid){
        int res = find_first_zero(tr[u].left , l , mid , ql , node_full << 1);
        if(res != -1) return res;
    }
    return find_first_zero(tr[u].right , mid + 1 , r , ql , node_full << 1 | 1);
}

bool is_smaller(int u , int v , int l , int r)
{
    if(tr[u].h == tr[v].h) return false;
    if(l == r) return tr[u].h < tr[v].h;
    int mid = (l + r) >> 1;
    if(tr[tr[u].right].h != tr[tr[v].right].h){
        return is_smaller(tr[u].right , tr[v].right , mid + 1 , r);
    }
    return is_smaller(tr[u].left , tr[v].left , l , mid);
}

int get_val(int u , int l , int r)
{
    if(tr[u].h == 0) return 0;
    if(l == r){
       return pw2[l];
    }
    int mid = (l + r) >> 1;
    return (get_val(tr[u].left , l , mid) + get_val(tr[u].right , mid + 1 , r)) % mod;
}

// 准备做Dijkstra
struct State{
    int u , root;

    bool operator > (const State &W) const{
        return is_smaller(W.root , root , 0 , M - 1);
    }
};

int n , m , start_point , end_point;
struct Edge{
    int to , weight;
};
vector<Edge> g[N];
int dist_root[N];
int pre[N];

void dijkstra()
{
    memset(dist_root , -1 , sizeof dist_root);
    priority_queue<State , vector<State> , greater<State> > pq;

    int root_zero = build(0 , M - 1);
    // root_zero也是dist[start_point];
    dist_root[start_point] = root_zero;
    pq.push({start_point , root_zero});
    while(!pq.empty())
    {
        auto t = pq.top();
        pq.pop();

        if(is_smaller(dist_root[t.u] , t.root , 0 , M - 1)) continue;

        int ver = t.u ;
        for(auto &edge : g[ver])
        {
            /// 计算dist[u] + 2^x
            int w = edge.weight , v = edge.to;
            int next_zero_pos = find_first_zero(dist_root[ver] , 0 , M - 1 , w , 1);
            int next_root = dist_root[ver];
            if(next_zero_pos > w) next_root = update_zero(next_root , root_zero , 0 , M - 1 , w , next_zero_pos - 1);
            next_root = update_one(next_root , 0 , M - 1 , next_zero_pos);

            if(dist_root[v] == -1 || is_smaller(next_root , dist_root[v] , 0 , M - 1)){
                dist_root[v] = next_root;
                pre[v] = ver;
                pq.push({v , next_root});
            }
        }
    }
}

void solve()
{
    init_hash();
    init_full_hash(1 , 0 , M - 1);

    cin >> n >> m;
    for(int i = 1 ; i <= m ; i++)
    {
        int u , v,  w;
        cin >> u >> v >> w;
        g[u].push_back({v , w});
        g[v].push_back({u , w});
    }
    cin >> start_point >> end_point;

    dijkstra();
    if(dist_root[end_point] == -1){
        cout << "-1\n";
    }
    else
    {
        int len = get_val(dist_root[end_point] , 0 , M - 1);
        cout << len << "\n";
        vector<int> path;

        int node = end_point;
        while(node != start_point){
            path.push_back(node);
            node = pre[node];
        }
        path.push_back(start_point);
        reverse(path.begin() , path.end());

        cout << path.size() << "\n";
        for(auto v : path){
            cout << v << " ";
        }
        cout << "\n";
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