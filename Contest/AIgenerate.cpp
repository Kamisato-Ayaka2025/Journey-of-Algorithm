#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 110, M = 1010; 

struct Edge {
    int to;
    int id;
};

vector<Edge> g[N];
vector<int> path;
bool used_edge[M]; 
int deg[N];
int n, m;

bool cmp(const Edge &a, const Edge &b) {
    return a.to < b.to;
}

void dfs(int u) {
    while (!g[u].empty()) {
        Edge e = g[u].back();
        g[u].pop_back(); 

        if (used_edge[e.id]) continue;
        used_edge[e.id] = true;
        
        dfs(e.to);
    }
    path.push_back(u);
}

void solve() {
    if (!(cin >> n >> m)) return;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
    }

    int odd_count = 0;
    int start_node = -1;
    vector<int> odds;

    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2 != 0) {
            odd_count++;
            odds.push_back(i);
        }
    }

    if (odd_count != 0 && odd_count != 2) {
        cout << 0 << endl;
        return;
    }

    if (odd_count == 2) {
        start_node = max(odds[0], odds[1]);
    } else {
        for (int i = n; i >= 1; i--) {
            if (deg[i] > 0) {
                start_node = i;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end(), cmp);
    }

    if (start_node != -1) dfs(start_node);

    if (path.size() != m + 1) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
        reverse(path.begin(), path.end()); 
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}