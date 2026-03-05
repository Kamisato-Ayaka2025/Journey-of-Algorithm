#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n;
vector<int> g[N];
int depth[N];
int pre[N]; 
bool vis[N];

void dfs_depth(int u, int fa) {
    pre[u] = fa;
    for (int v : g[u]) {
        if (v == fa) continue;
        depth[v] = depth[u] + 1;
        dfs_depth(v, u);
    }
}

void solve() {
    if (!(cin >> n)) return;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    depth[1] = 0;
    dfs_depth(1 , 0);
    int a = 1, maxd = -1;
    for (int i = 1; i <= n; i++) {
        if (depth[i] > maxd) {
            maxd = depth[i];
            a = i;
        }
    }

    depth[a] = 0;
    dfs_depth(a , 0); 
    int b = a;
    maxd = -1;
    for (int i = 1; i <= n; i++) {
        if (depth[i] > maxd) {
            maxd = depth[i];
            b = i;
        }
    }
    int diameter = maxd;

    queue<int> q;
    for (int i = 1; i <= n; i++) vis[i] = false; 

    int curr = b;
    while (curr != 0) {
        vis[curr] = true;
        depth[curr] = 0; 
        q.push(curr);
        curr = pre[curr]; 
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }

    int c = -1;
    int max_to_path = -1;
    for (int i = 1; i <= n; i++) {
        if (i == a || i == b) continue; 
        if (depth[i] > max_to_path) {
            max_to_path = depth[i];
            c = i;
        }
    }

    if (c == -1) { // 特判，如果这个树是一条链
        for (int i = 1; i <= n; i++) {
            if (i != a && i != b) {
                c = i;
                max_to_path = 0;
                break;
            }
        }
    }

    cout << diameter + max_to_path << "\n";
    cout << a << " " << b << " " << c << "\n";
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