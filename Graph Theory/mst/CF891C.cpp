#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 5e5 + 10;

int n , m;

class Edge{
public:
    int u , v , w ,eid;

    bool operator < (const Edge &W) const{
        return w < W.w;
    }
};

class Query{
public:
    int u , v , qid;
};

class History{
public:
    int u , v;
};

Edge edge[N];

vector<Query> weight_to_query[N];
vector<History> history;
int p[N] , sz[N];
bool ans[N];

int find(int x)
{
    while(p[x] != x) x = p[x];
    return p[x];
}

void unite(int u , int v , bool backtrack)
{
    u = find(u);
    v = find(v);
    if(u != v)
    {
        if(sz[u] < sz[v]) swap(u , v);
        if(backtrack) history.push_back({u , v});
        p[v] = u;
        sz[u] += sz[v]; 
    }
}

void rollback(int history_size)
{
    while((int)history.size() > history_size)
    {
        auto t = history.back();
        history.pop_back();

        sz[t.u] -= sz[t.v];
        p[t.v] = t.v;
    }
}

void init()
{
    for(int i = 1 ; i <= n ; i++){
        p[i] = i;
        sz[i] = 1;
    }
}

void solve()
{
    cin >> n >> m;
    init();
    for(int i = 1 ; i <= m ; i++)
    {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        edge[i].eid = i;
    }

    int q;
    cin >> q;
    for(int i = 1 ; i <= q ; i++)
    {
        int k;
        cin >> k;
        while( k-- )
        {
            int eid;
            cin >> eid;
            int u = edge[eid].u , v = edge[eid].v , w = edge[eid].w;
            weight_to_query[w].push_back({u , v , i});
        }
    }

    vector<Edge> sort_edge;
    for(int i = 1 ; i <= m ; i++) sort_edge.push_back(edge[i]);
    sort(sort_edge.begin() , sort_edge.end());

    int edge_idx = 0;
    for(int w = 1 ; w < N ; w++)
    {
        // 没有查询，直接并
        if(weight_to_query[w].empty())
        {
            while(edge_idx < (int)sort_edge.size() && sort_edge[edge_idx].w == w){
                unite(sort_edge[edge_idx].u , sort_edge[edge_idx].v , false);
                edge_idx++;
            }
            continue;
        }

        

        // 有查询，挨个做
        for(int i = 0 ; i < (int)weight_to_query[w].size() ; )
        {   // 先找同个query的
            // 由于插入的顺序，同个query必定在一起
            int j = i;
            int current_qid = weight_to_query[w][i].qid;
            while(j < (int)weight_to_query[w].size() && weight_to_query[w][j].qid == current_qid){
                j++;
            }

            if(ans[current_qid]){
                i = j;
                continue;
            }

            // 然后尝试将这些连边
            int snapshot = (int)history.size();
            for(int k = i ; k < j ; k++)
            {
                int u = find(weight_to_query[w][k].u);
                int v = find(weight_to_query[w][k].v);

                if(u == v){
                    ans[current_qid] = true;
                    break;
                }
                else{
                    unite(u , v ,  true);
                }
            }
            rollback(snapshot);
            i = j;
        }

        // 最后将这一层全部合并
        while(edge_idx < (int)sort_edge.size() && sort_edge[edge_idx].w == w){
            unite(sort_edge[edge_idx].u , sort_edge[edge_idx].v , false);
            edge_idx++;
        }
    }

    for(int i = 1 ; i <= q ; i++)
    {
        if(ans[i]) cout << "NO\n";
        else cout << "YES\n";
    }
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt"  ,"w"  ,stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}