#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INF 0x3f3f3f3f
const int N = 200010;
const int M = N * 4; 

int n, q_num;
int headg[N], tog[M], nxtg[M], cntg;
int headv[N], tov[M], nxtv[M], cntv;

int depth[N], up[N][20];
int dfn[N], timer;

int chosen[N * 2], k_cnt, unique_cnt;
int minTime[N], findViruse[N];
int v_speed[N];
bool vis[N];

void addEdgeG(int u, int v) {
    tog[++cntg] = v;
    nxtg[cntg] = headg[u];
    headg[u] = cntg;
}

void addEdgeV(int u, int v) {
    tov[++cntv] = v;
    nxtv[cntv] = headv[u];
    headv[u] = cntv;
}

class Node {
public:
    int id, time, dist, city;
    Node(int i, int t, int d, int c) : id(i), time(t), dist(d), city(c) {};
    bool operator > (const Node &W) const {
        if (time != W.time) return time > W.time;
        return id > W.id;
    }
};

void dfs_pre(int u, int f) {
    dfn[u] = ++timer;
    depth[u] = depth[f] + 1;
    up[u][0] = f;
    for (int j = 1; j < 20; j++)
        up[u][j] = up[up[u][j - 1]][j - 1];
    
    for (int i = headg[u]; i; i = nxtg[i]) {
        int v = tog[i];
        if (v == f) continue;
        dfs_pre(v, u);
    }
}

int get_lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int j = 19; j >= 0; j--)
        if (depth[up[a][j]] >= depth[b]) a = up[a][j];
    if (a == b) return a;
    for (int j = 19; j >= 0; j--)
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    return up[a][0];
}

bool cmp(int a, int b) {
    return dfn[a] < dfn[b];
}

void build_Virtual_Tree() {
    sort(chosen + 1, chosen + 1 + k_cnt, cmp);
    int len = k_cnt;
    for (int i = 1; i < k_cnt; i++) {
        chosen[++len] = get_lca(chosen[i], chosen[i + 1]);
    }
    sort(chosen + 1, chosen + 1 + len, cmp);

    unique_cnt = 1;
    for (int i = 2; i <= len; i++) {
        if (chosen[i] != chosen[unique_cnt])
            chosen[++unique_cnt] = chosen[i];
    }


    for (int i = 1; i < unique_cnt; i++) {
        int lc = get_lca(chosen[i], chosen[i + 1]);
        addEdgeV(lc, chosen[i + 1]);
        addEdgeV(chosen[i + 1], lc);
    }
}

priority_queue<Node, vector<Node>, greater<Node>> pq;

void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        addEdgeG(u, v);
        addEdgeG(v, u);
    }
    dfs_pre(1, 0);

    cin >> q_num;
    while (q_num--) {
        int s, t; cin >> s >> t;
        while (!pq.empty()) pq.pop();
        k_cnt = 0;
        cntv = 0;

        vector<pair<int, int>> virus_start(s + 1);
        for (int i = 1; i <= s; i++) {
            cin >> virus_start[i].first >> v_speed[i];
            chosen[++k_cnt] = virus_start[i].first;
        }

        vector<int> importantCity(t + 1);
        for (int i = 1; i <= t; i++) {
            cin >> importantCity[i];
            chosen[++k_cnt] = importantCity[i];
        }

        build_Virtual_Tree();

        for (int i = 1; i <= unique_cnt; i++) {
            int city = chosen[i];
            minTime[city] = INF;
            findViruse[city] = -1;
            vis[city] = false;
        }

        for (int i = 1; i <= s; i++) {
            int city = virus_start[i].first;
            minTime[city] = 0;
            findViruse[city] = i;
            pq.emplace(i, 0, 0, city);
        }

        while (!pq.empty()) {
            Node curr = pq.top(); pq.pop();
            int u = curr.city;
            if (vis[u]) continue;
            vis[u] = true;

            for (int i = headv[u]; i; i = nxtv[i]) {
                int v = tov[i];
                if (vis[v]) continue;
                
                int d_uv = abs(depth[u] - depth[v]);
                int total_dist = curr.dist + d_uv;
                int v_idx = curr.id;
                int arrival_time = (total_dist + v_speed[v_idx] - 1) / v_speed[v_idx];

                if (arrival_time < minTime[v] || (arrival_time == minTime[v] && v_idx < findViruse[v])) {
                    minTime[v] = arrival_time;
                    findViruse[v] = v_idx;
                    pq.emplace(v_idx, arrival_time, total_dist, v);
                }
            }
        }

        for (int i = 1; i <= t; i++) {
            cout << findViruse[importantCity[i]] << (i == t ? "" : " ");
        }
        cout << "\n";

        for (int i = 1; i <= unique_cnt; i++) {
            headv[chosen[i]] = 0;
        }
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
    solve();
    return 0;
}