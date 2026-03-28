#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 200005;
const int MAXM = 400005;

int head[MAXM], nxt[MAXN * 2], to[MAXN * 2], edge_id[MAXN * 2];
int edge_cnt;
int degree[MAXM];
bool used[MAXN];
vector<int> res;

void dfs(int u , int f) {
    while (head[u] != -1) {
        int i = head[u];
        head[u] = nxt[i]; 

        int id = edge_id[i];
        if (used[id]) continue;
        used[id] = true;

        int v = to[i];
        if(v == f) continue;
        dfs(v , u);
        res.push_back(id); 
    }
}

inline void add_edge(int u, int v, int id) {
    to[edge_cnt] = v;
    edge_id[edge_cnt] = id;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    struct RawEdge { int v, p, id; };
    vector<RawEdge> raw_edges;
    vector<int> tmp1, tmp2;

    for (int i = 1; i <= n; i++) {
        int v, p;
        cin >> v >> p;
        tmp1.push_back(v);
        tmp2.push_back(p);
        raw_edges.push_back({v, p, i});
    }

    // 离散化
    sort(tmp1.begin(), tmp1.end());
    tmp1.erase(unique(tmp1.begin(), tmp1.end()), tmp1.end());
    sort(tmp2.begin(), tmp2.end());
    tmp2.erase(unique(tmp2.begin(), tmp2.end()), tmp2.end());

    int len1 = tmp1.size();
    int total_node = len1 + tmp2.size();

    edge_cnt = 0;
    for (int i = 0; i <= total_node; i++) {
        head[i] = -1;
        degree[i] = 0;
    }
    for (int i = 1; i <= n; i++) used[i] = false;
    res.clear();

    for (auto &e : raw_edges) {
        int u = lower_bound(tmp1.begin(), tmp1.end(), e.v) - tmp1.begin() + 1;
        int v = lower_bound(tmp2.begin(), tmp2.end(), e.p) - tmp2.begin() + 1 + len1;
        add_edge(u, v, e.id);
        add_edge(v, u, e.id);
        degree[u]++;
        degree[v]++;
    }

    int start_node = -1;
    int odd_count = 0;
    for (int i = 1; i <= total_node; i++) {
        if (degree[i] % 2 != 0) {
            odd_count++;
            if (start_node == -1) start_node = i;
        }
    }

    if (odd_count > 2) {
        cout << "NO\n";
        return;
    }

    if (start_node == -1) {
        for (int i = 1; i <= total_node; i++) {
            if (degree[i] > 0) {
                start_node = i;
                break;
            }
        }
    }

    if (start_node != -1) dfs(start_node , -1);

    if ((int)res.size() != n) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            cout << res[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
    }
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