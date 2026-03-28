#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

const int mod = 998244353 , N = 2e6 + 10;

int n , m;
vector<int> g[N];
int in[N];

LL frac = 1;
LL sz[N] , sz_mul[N];

void pre()
{
    for(int i = 1 ; i <= n + 1; i++){
        frac = (frac * i) % mod;
    }
}

void dfs(int u)
{
    sz[u] = sz_mul[u] = 1;
    for(int v : g[u])
    {
        dfs(v);
        sz[u] += sz[v];
        sz_mul[u] = (sz_mul[u] * sz_mul[v]) % mod;
    }
    sz_mul[u] = (sz_mul[u] * sz[u]) % mod;
}

LL qmi(LL x ,  LL k)
{
    LL res =1;
    while(k)
    {
        if(k & 1) res = (res * x) % mod;
        x = (x * x) % mod;
        k >>= 1;
    }
    return res;
}

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= m ; i++)
    {
        int u , v;
        cin >> u >> v;
        g[v].push_back(u);
        in[u]++;
    }

    for(int i = 1 ; i <= n ; i++)
    {
        if(!in[i]){
            g[0].push_back(i);
        }
    }

    pre();
    dfs(0);

    if(sz[0] != n + 1){
        cout << "0\n";
        return;
    }

    LL inv = qmi(sz_mul[0] , mod - 2);
    cout << (frac * inv) % mod << "\n";
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