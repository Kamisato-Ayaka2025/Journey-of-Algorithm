#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10 , mod = 998244353;

class Edge{
public:
    int from , to , weight , eid;
    Edge(int f , int t , int w , int id) : from(f) , to(t) , weight(w) , eid(id) {};

    inline int theOther(int x){
        return from ^ to ^ x;
    }

    bool operator < (const Edge &W) const{
        return weight < W.weight;
    }
};

LL res;
LL S;
int n;
int p[N] , sz[N];
vector<Edge> edge;

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void init()
{
    edge.clear();
    res = 1ll;
    for(int i = 1 ; i <= n ; i++)
    {
        p[i] = i;
        sz[i] = 1;
    }
}

LL qmi(LL x , LL k)
{
    LL res = 1;
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
    cin >> n >> S;
    init();
    for(int i = 1 ; i < n ; i++)
    {
        int u , v, w;
        cin >> u >> v >> w;
        edge.emplace_back(u , v , w , i);
    }

    sort(edge.begin() , edge.end());
    for(auto e : edge)
    {
        int u = e.from , v = e.to , w = e.weight;

        int root_u = find(u) , root_v = find(v);
        if(root_u != root_v)
        {   // 对于树实际上不用判断
            int sz1 = sz[root_u] , sz2 = sz[root_v];
            res = res * qmi(max(S - w + 1, 0ll) , (LL)sz1 * sz2 - 1) % mod;

            p[root_u] = root_v;
            sz[root_v] += sz[root_u];
        }
    }

    cout << res << "\n";
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
    while( T-- ) solve();

    return 0;
}