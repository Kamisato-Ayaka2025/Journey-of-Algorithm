#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 500010, M = 1000010; 

int n, m;
int h[N], e[M], ne[M], idx;
int deg[N];
bool used_edge[M / 2 + 7]; // 标记边是否被欧拉回路访问过
bool vis_balance[N];       // 用于森林 DFS 平衡度数
struct Edge {
    int to, id;
};
vector<Edge> adj0[N];      // 存储 c=0 的边用于构建森林
bool selected0[M / 2 + 7]; // 记录哪些 c=0 的边被选中

void add(int u, int v) {
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

void dfs_balance(int u, int p, int edge_id) {
    vis_balance[u] = true;
    for (auto& edge : adj0[u]) {
        if (vis_balance[edge.to]) continue;
        dfs_balance(edge.to, u, edge.id);
    }
    if (deg[u] % 2 != 0 && p != -1) {
        selected0[edge_id] = true;
        deg[u]++;
        deg[p]++;
    }
}

vector<int> path;
void find_euler(int u) {
    while (h[u] != -1) {
        int i = h[u];
        h[u] = ne[i]; 
        if (used_edge[i / 2]) continue;
        used_edge[i / 2] = true;
        find_euler(e[i]);
    }
    path.push_back(u);
}

struct RawEdge {
    int u, v, c;
};

void solve() {
    cin >> n >> m;
    idx = 0;
    path.clear();
    for (int i = 1; i <= n; i++) {
        h[i] = -1;
        deg[i] = 0;
        vis_balance[i] = false;
        adj0[i].clear();
    }
    for (int i = 0; i <= m; i++) {
        used_edge[i] = false;
        selected0[i] = false;
    }

    vector<RawEdge> raw_edges(m);
    for (int i = 0; i < m; i++) {
        cin >> raw_edges[i].u >> raw_edges[i].v >> raw_edges[i].c;
        if (raw_edges[i].c == 1) {
            deg[raw_edges[i].u]++;
            deg[raw_edges[i].v]++;
        } else {
            adj0[raw_edges[i].u].push_back({raw_edges[i].v, i});
            adj0[raw_edges[i].v].push_back({raw_edges[i].u, i});
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!vis_balance[i]) {
            dfs_balance(i, -1, -1);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2 != 0) {
            // 这样就无法构成了
            cout << "No" << endl;
            return;
        }
    }

    for (int i = 0; i < m; i++) {
        if (raw_edges[i].c == 1 || selected0[i]) {
            add(raw_edges[i].u, raw_edges[i].v);
            add(raw_edges[i].v, raw_edges[i].u);
        }
    }

    find_euler(1);

    cout << "Yes\n";
    cout << path.size() - 1 << "\n";
    for(int v : path){
        cout << v << " ";
    }
    cout << "\n";
}

// #define _DEBUG
int main() {
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" , "w" , stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}