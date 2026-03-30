#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int N = 5e5 + 10;
int n;
int a[N] , b[N];
int p[1 << 20];
int h[1 << 20] , e[N << 1] , ne[N << 1] , idx;
vector<int> res;
bool used[N];

void addEdge(int u , int v)
{
    e[idx] = v,  ne[idx] = h[u] , h[u] = idx++;
}

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

bool check(int k)
{
    int mask = (1 << k) - 1;
    vector<int> degree(mask + 1, 0);
    // 初始化并查集
    for(int i = 0 ; i < (1 << k) ;i++){
        p[i] = i;
    }

    int comp_cnt = 0;
    for(int i = 1 ; i <= n ; i++)
    {
        int u = a[i] & mask , v = b[i] & mask;
        degree[u]++ , degree[v]++;
        if(find(u) != find(v)){
            p[find(u)] = find(v);
        }
    }

    bool ok = true;
    for(int i = 0 ; i < (1 << k) ; i++){
        if(degree[i] % 2){
            ok = false;
            break;
        }
    }

    // 再看看是否有度数的点都在一个连通块
    for(int i = 0 ; i < (1 << k); i++)
    {
        if(degree[i] > 0 && find(i) == i){
            comp_cnt++;
        }
    }

    if(comp_cnt > 1) ok = false;
    
    // return
    return ok;
}

void dfs(int u)
{
    while(h[u] != -1)
    {
        int idx = h[u];
        h[u] = ne[h[u]];

        if(used[idx / 2]) continue;
        used[idx / 2] = true;

        int v = e[idx];
        dfs(v);

        if(idx % 2 == 0){ // u -> v;
            int edge_id = idx / 2;
            res.push_back(edge_id * 2 + 2);
            res.push_back(edge_id * 2 + 1);
        }
        else{ // v -> u
            int edge_id = idx / 2;
            res.push_back(edge_id * 2 + 1);
            res.push_back(edge_id * 2 + 2);
        }
    }
}

void solve()
{
    memset(h , -1 , sizeof h);
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i] >> b[i];
    }

    // 先确定最大可行的k
    int max_k = 20;
    for(int i = 20 ; i >= 0 ; i--){
        if(check(i)){
            max_k = i;
            break;
        }
    }

    int start_node = -1;
    int mask = (1 << max_k) - 1;
    for(int i = 1 ; i <= n ; i++)
    {
        int u = a[i] & mask , v = b[i] & mask;
        addEdge(u , v);
        addEdge(v , u);
        start_node = u;
    }

    if(start_node != -1) dfs(start_node);

    cout << max_k << "\n";
    for(int v : res){
        cout << v << " ";
    }
    cout << "\n";
    return; 
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

    solve();

    return 0;
}