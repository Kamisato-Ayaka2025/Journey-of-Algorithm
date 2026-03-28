#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

class Edge{
public:
    int from , to , weight , edgeID;

    Edge(int f , int t , int w , int eid) : from(f) , to(t) , weight(w) , edgeID(eid) {};

    inline int theOther(int x){
        return from ^ to ^ x;
    }

    bool operator < (const Edge &W) const{
        return weight < W.weight;
    }

    bool operator > (const Edge &W) const{
        return weight > W.weight;
    }
};

priority_queue<Edge> pq1;
priority_queue<Edge , vector<Edge> , greater<Edge> > pq2;

int n , m ;
LL s;

int p[N];

void init()
{
    for(int i = 1 ; i <= n ; i++){
        p[i] = i;
    }
}

int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void solve()
{   
    cin >> n >> m >> s;
    init();

    for(int i = 0 ; i < m ; i++)
    {
        int a , b , s;
        cin >> a >> b >> s;
        pq1.push(Edge(a , b , s , i));
    }

    for(int i = 0 ; i < m ; i++)
    {
        auto t = pq1.top();
        pq1.pop();

        int a = t.from , b = t.to;
        LL w = t.weight;

        int pa = find(a) , pb = find(b);
        if(pa == pb)
        {
            pq2.push(t);
        }
        else
        {
            p[pa] = pb;
        }
    }

    vector<int> res;
    while(!pq2.empty())
    {
        auto t = pq2.top();
        pq2.pop();

        LL w = t.weight;
        if(s >= w){
            s -= w;
            res.push_back(t.edgeID + 1);
        }
        else break;
    }

    sort(res.begin() , res.end());
    cout << (int)res.size() << "\n";
    for(int v : res) cout << v << " ";
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