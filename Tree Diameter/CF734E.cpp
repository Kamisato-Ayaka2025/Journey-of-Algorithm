#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

int n;
int color[N], id[N], cnt;
bool vis[N];
vector<int> g[N]; 
vector<int> g1[N]; 
int depth[N];

// 缩点 DFS
void dfs_comp(int u, int col, int cmp) {
    vis[u] = true;
    id[u] = cmp;
    for (int v : g[u]) {
        if (!vis[v] && color[v] == col) {
            dfs_comp(v, col, cmp);
        }
    }
}

// 求深度 DFS
void dfs_depth(int u, int fa, int d) {
    depth[u] = d;
    for (int v : g1[u]) {
        if (v == fa) continue;
        dfs_depth(v, u, d + 1);
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> color[i];
    
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        edges.push_back({u, v}); 
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs_comp(i, color[i], ++cnt);
        }
    }

    // 构建缩点后的图
    for (auto& edge : edges) {
        int u = id[edge.first];
        int v = id[edge.second];
        if (u != v) {
            g1[u].push_back(v);
            g1[v].push_back(u);
        }
    }

    if (cnt <= 1) {
        cout << 0 << endl;
        return;
    }

    dfs_depth(1, 0, 0);
    int maxd = -1, start_node = 1;
    for (int i = 1; i <= cnt; i++) {
        if (depth[i] > maxd) {
            maxd = depth[i];
            start_node = i;
        }
    }

    dfs_depth(start_node, 0, 0);
    int diameter = 0;
    for (int i = 1; i <= cnt; i++) {
        diameter = max(diameter, depth[i]);
    }

    cout << (diameter + 1) / 2 << "\n";
}

// #define _DEBUG
int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}