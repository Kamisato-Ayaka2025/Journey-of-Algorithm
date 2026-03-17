#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define INF 1e18

const int N = 1e3 + 10;
typedef long long LL;
typedef pair<LL , int> PII;

int n , m;
int e[N * 2] , ne[N * 2] , w[N * 2] , h[N] , idx;
int s[N] , S_max;
LL dist[N][N];
bool st[N];

void addEdge(int a , int b , int c)
{
    e[idx] = b , ne[idx] = h[a] , w[idx] = c, h[a] = idx++;
}

class State{
public:
    LL d;
    int pos , min_factor;
    State(LL d , int p , int mini) : d(d) , pos(p) , min_factor(mini) {};
    bool operator > (const State &W) const{
        return d > W.d;
    }
};

void Dijkstra()
{
    for(int i = 1 ; i <= n ; i++){
        for(int j = 0 ; j <= S_max ; j++) dist[i][j] = INF;
    }
    priority_queue<State , vector<State> , greater<State> > heap;

    dist[1][s[1]] = 0ll;
    heap.emplace(dist[1][s[1]] , 1 , s[1]);
    while(!heap.empty())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.pos , factor = t.min_factor ;
        LL d = t.d;
        if(d > dist[ver][factor]) continue;
        factor = min(factor , s[ver]);
        dist[ver][factor] = min(dist[ver][factor] , d);
        for(int i = h[ver] ; ~i ; i = ne[i])
        {
            int j = e[i];
            if(dist[j][factor] > d + (LL)factor * w[i])
            {
                dist[j][factor] = d + (LL)factor * w[i];
                heap.emplace(dist[j][factor] , j , factor);
            }
        }
    }
}   

void init()
{
    for(int i = 1 ; i <= n ; i++){
        h[i] = -1;
        st[i] = false;
    }
    idx = 0;
    S_max = 0;
}

void solve()
{
    cin >> n >> m;
    init();

    for(int i = 1 ; i <= m ; i++)
    {
        int a , b , c;
        cin >> a >> b >> c;
        addEdge(a , b , c);
        addEdge(b , a , c);
    }

    for(int i = 1 ; i <= n ;i++){
        cin >> s[i];
        S_max = max(S_max , s[i]);
    }

    Dijkstra();
    LL res = INF;
    for(int i = 1 ; i <= S_max ; i++){
        res = min(res , dist[n][i]);
    }
    cout << res << "\n";
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

    int T;
    cin >> T;
    while( T-- ){
        solve();
    }
    return 0;
}