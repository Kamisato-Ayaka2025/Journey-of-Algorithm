#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

#define INF 0x3f3f3f3f

class Node{
public:
    int sum , mx_pre , mx_suf , min_pre , min_suf , mx_seg , min_seg;

    static Node merge(Node &a , Node &b)
    {   // 需要注意的是 , a必须是下端节点 ，而b是上端节点
        Node res;
        
        res.sum = a.sum + b.sum;
        res.mx_pre = max(a.mx_pre , a.sum + b.mx_pre);
        res.mx_suf = max(b.mx_suf , b.sum + a.mx_suf);

        res.min_pre = min(a.min_pre , a.sum + b.min_pre);
        res.min_suf = min(b.min_suf , b.sum + a.min_suf);

        res.mx_seg = max(a.mx_seg , max(b.mx_seg , a.mx_suf + b.mx_pre));
        res.min_seg = min(a.min_seg , min(b.min_seg , a.min_suf + b.min_pre));

        return res;
    }

    static Node reverse(Node &a)
    {
        swap(a.mx_pre , a.mx_suf);
        swap(a.min_pre , a.min_suf);
        return a;
    }
};

int q , cur_mx_node;
vector<int> g[N];
int w[N];
int up[N][20] , depth[N];
Node info[N][20];

void add_node(int v , int x)
{
    cur_mx_node++;
    int u = cur_mx_node;

    for(int j = 0; j < 20; j++) {
        up[u][j] = 0;
    }
    
    up[u][0] = v;
    depth[u] = depth[v] + 1;

    int mx_val = max(0 , x) , min_val = min(0 , x);
    info[u][0] = {x , mx_val , mx_val , min_val , min_val , mx_val , min_val};
    for(int j = 1 ; j < 20 ; j++)
    {
        up[u][j] = up[up[u][j - 1]][j - 1];
        info[u][j] = Node::merge(info[u][j - 1] , info[up[u][j - 1]][j - 1]);
    }
}

int lca(int a , int b)
{
    if(depth[a] < depth[b]) swap(a , b);

    int f = depth[a] - depth[b];
    for(int j = 19 ; j >= 0 ; j--){
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

Node kth(int u , int k)
{   // 查向上k步的必要信息
    Node res;
    bool first = true;
    for(int j = 19 ; j >= 0 ; j--)
    {
        if(k & (1 << j))
        {
            if(first){
                res = info[u][j];
                first = false;
            }
            else{
                res = Node::merge(res , info[u][j]);
            }
            u = up[u][j];
        }
    }
    return res;
}

void solve()
{
    cin >> q;
    cur_mx_node = w[1] = 1;
    depth[1] = 1;
    for(int j = 0 ; j < 20 ; j++) up[1][j] = 0;
    for(int j = 0 ; j < 20 ; j++ ) info[1][j] = {1 , 1 , 1 , 0 , 0 , 1 , 0};
    for(int j = 0 ; j < 20 ; j++ ) info[0][j] = {0 , -INF , -INF , INF , INF , -INF , INF};
    while( q-- )
    {
        char op[2];
        cin >> op;
        if(op[0] == '+')
        {
            int v , x;
            cin >> v >> x;
            add_node(v , x);
        }
        else
        {
            int u, v, k;
            cin >> u >> v >> k;
            int x = lca(u, v);

           
            int ans_min, ans_max;

            if(x == v)
            {
                Node resU = kth(u , depth[u] - depth[x] + 1);
                ans_min = resU.min_seg;
                ans_max = resU.mx_seg;
            }
            else if(x == u)
            {
                Node resD = kth(v , depth[v] - depth[x] + 1);
                ans_min = resD.min_seg;
                ans_max = resD.mx_seg;
            }
            else
            {
                Node resU = kth(u, depth[u] - depth[x] + 1);
                Node resD = kth(v, depth[v] - depth[x]);
                ans_max = max({resU.mx_seg, resD.mx_seg, resU.mx_suf + resD.mx_suf});
                ans_min = min({resU.min_seg, resD.min_seg, resU.min_suf + resD.min_suf});
            }

            if(k >= ans_min && k <= ans_max) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return;
}

 //#define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r", stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while( T-- ) solve();
    return 0;
}