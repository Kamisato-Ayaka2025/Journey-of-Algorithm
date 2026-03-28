#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef long long LL;
typedef pair<int , int> PII;
const int N = 5e5 + 10;
int n;

// 每个点
class Point{
public:
    int l , r , x;
};

Point a[N];

// 扫描线辅助
class Event{
public:
    int pos;
    int idx;
    Event(int p , int id) : pos(p) , idx(id) {};

    bool operator < (const Event &W) const {
        if(pos != W.pos) return pos < W.pos;
        return idx < W.idx; // 优先处理删除操作
    }
};

// 每条边
class Edge{
public:
    int from , to , weight;
    Edge(int f , int t , int w) : from(f) , to(t) , weight(w) {};

    bool operator < (const Edge &W) const{
        return weight < W.weight;
    }
};

vector<Edge> edge;
int p[N];

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void init()
{
    edge.clear();
    for(int i = 1 ; i <= n ; i++)
    {
        p[i] = i;
    }
}

void solve()
{
    cin >> n;
    init();
    vector<int> tmp;
    vector<Event> event;

    // 离散化
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> a[i].l >> a[i].r >> a[i].x;
        tmp.push_back(a[i].l);
        tmp.push_back(++a[i].r);
    }

    sort(tmp.begin() , tmp.end());
    tmp.erase(unique(tmp.begin() , tmp.end()) , tmp.end());

    for(int i = 1 ; i <= n ; i++)
    {
        a[i].l = lower_bound(tmp.begin() , tmp.end() , a[i].l) - tmp.begin() + 1;
        a[i].r = lower_bound(tmp.begin() , tmp.end() , a[i].r) - tmp.begin() + 1;
        event.emplace_back(a[i].l , i);
        event.emplace_back(a[i].r , -i);
    }

    sort(event.begin() , event.end());

    // 扫描线
    set<PII> S;
    for(auto t : event)
    {
        int position = t.pos , id = t.idx;
        if(id > 0)
        {
            auto it = S.insert({a[id].x , id}).first;
            if(it != S.begin())
            {
                int id1 = prev(it) -> second;
                edge.emplace_back(id , id1 , a[id].x - a[id1].x);
            }
            if(next(it) != S.end())
            {
                int id1 = next(it) -> second;
                edge.emplace_back(id , id1 , a[id1].x - a[id].x);
            }
        }
        else
        {
            S.erase({a[-id].x , -id});
        }
    }

    // Kruskal
    int cnt = 0;
    LL res = 0;
    sort(edge.begin() , edge.end());
    for(auto e : edge)
    {
        int u = e.from , v = e.to , w = e.weight;
        int root_u = find(u) , root_v = find(v);
        if(root_u != root_v)
        {
            res += (LL)w;
            p[root_u] = root_v;
            cnt++;
        }
    }


    cout << (cnt == n - 1 ? res : -1) << "\n";
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