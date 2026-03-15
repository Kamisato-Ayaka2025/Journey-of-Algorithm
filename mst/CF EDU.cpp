#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int N = 2e5 + 10;

typedef long long LL;

class Edge{
public:
    int from , to , weight ,edgeID;
    Edge(int f , int t , int w  ,int eid) : from(f) , to(t) , weight(w) ,edgeID(eid) {};

    inline int theOther(int x){
        return from ^ to ^ x;
    }

    bool operator > (const Edge &W) const{
        return weight > W.weight;
    }
};

int n , m;
int p[N]; 
priority_queue<Edge , vector<Edge> , greater<Edge> > pq;

void init()
{
    for(int i = 1 ; i <= n ; i++) p[i] = i;
}

int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void solve()
{
    cin >> n >> m;
    init();
    for(int i = 0 ; i < m ; i++)
    {   
        int a , b , w;
        cin >> a >> b >> w;
        pq.push(Edge(a , b , w , i));
    }

    LL sum = 0;
    for(int i = 0 ; i < m ; i++)
    {
        auto t = pq.top();
        pq.pop();

        int a = t.from , b = t.to;
        int pa = find(a) , pb = find(b);
        LL w = t.weight;

        if(pa != pb)
        {
            p[pa] = pb;
            sum += w;
        }
    }

    cout << sum << "\n";
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