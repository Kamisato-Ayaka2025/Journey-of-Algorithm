#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 100010;

struct Edge {
    int from, to;
    inline int theOther(int x) { return from ^ to ^ x; }
};

int n, m;
vector<int> g[N], g1[N];
vector<Edge> edges;
int dfn[N], low[N], timestamp;
int id[N], comp_cnt, rep[N];
stack<int> stk;

void tarjan(int u, int f_eid) {
    dfn[u] = low[u] = ++timestamp;
    stk.push(u);

    for (int eid : g[u]) {
        if (eid == f_eid) continue;
        int v = edges[eid].theOther(u);
        if (!dfn[v]) {
            tarjan(v, eid);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        comp_cnt++;
        rep[comp_cnt] = u; 
        while (true) {
            int t = stk.top();
            stk.pop();
            id[t] = comp_cnt;
            if (t == u) break;
        }
    }
}

pair<int, int> bfs(int start_node) {
    static int dist[N];
    for (int i = 1; i <= comp_cnt; i++) dist[i] = -1;
    
    queue<int> q;
    q.push(start_node);
    dist[start_node] = 0;

    int farthest_node = start_node;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist[u] > dist[farthest_node]) farthest_node = u;

        for (int v : g1[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return {farthest_node, dist[farthest_node]};
}

void solve() {
    if (!(cin >> n >> m)) return;

    // 清理数据
    edges.clear();
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        g1[i].clear();
        dfn[i] = 0;
    }
    timestamp = 0;
    comp_cnt = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        g[u].push_back(i);
        g[v].push_back(i);
    }

    tarjan(1, -1);
    for (int i = 0; i < m; i++) {
        int u = edges[i].from, v = edges[i].to;
        if (id[u] != id[v]) {
            g1[id[u]].push_back(id[v]);
            g1[id[v]].push_back(id[u]);
        }
    }

    if (comp_cnt <= 1) {
        if (n >= 2) cout << "1 2" << endl;
        else cout << "1 1" << endl;
        return;
    }
    int a = bfs(1).first;  
    int b = bfs(a).first;        

    // 4. 输出原图中的节点 ID
    cout << rep[a] << " " << rep[b] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}