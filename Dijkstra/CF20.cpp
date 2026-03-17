#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define INF 1e18
typedef long long LL;
typedef pair<LL , int> PII;

const int N = 1e5 + 10 , mod = 1e9 + 7;

int e[N * 2] , ne[N * 2] , h[N] , idx , w[N * 2];

void addEdge(int a , int b , int c)
{
    e[idx] = b , ne[idx] = h[a] , w[idx] = c , h[a] = idx++;
}

int n , m;
LL dist[N];
bool st[N];
int from[N];

void dijkstra()
{
    for(int i = 1 ; i <= n ; i++) dist[i] = INF;

    priority_queue<PII , vector<PII> , greater<PII> > heap;
    dist[1] = 0ll;
    from[1] = 1;

    heap.push({0ll , 1});

    while(!heap.empty())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second;
        // LL d = t.first;

        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver] ; ~i ; i = ne[i])
        {
            int j = e[i];
            if(j == from[ver]) continue;

            if(dist[j] > dist[ver] + w[i]){
                dist[j] = dist[ver] + w[i];
                from[j] = ver;
                heap.push({dist[j] , j});
            }
        }
    }

}

void solve()
{
    memset(h , -1 , sizeof h);
    cin >> n >> m;
    for(int i = 1 ; i <= m ; i++)
    {
        int u , v , w;
        cin >> u >> v >> w;
        addEdge(u , v , w);
        addEdge(v , u , w);
    }

    dijkstra();

    if(dist[n] == INF){
        cout << -1 << "\n";
    }
    else{
        vector<int> res;
        int node = n;
        do{
            res.push_back(node);
            node = from[node];
        }while(node != from[node]);

        res.push_back(1);

        reverse(res.begin() , res.end());

        for(auto v : res){
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
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}