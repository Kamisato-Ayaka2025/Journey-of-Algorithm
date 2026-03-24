#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

inline char get_char() {
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}
inline int read() {
    int x = 0; char ch = get_char();
    while (ch < '0' || ch > '9') ch = get_char();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = get_char();
    return x;
}

const int N = 200010;
const int M = N * 4;
const int INF = 0x3f3f3f3f;

int n, q_num;
int headg[N], tog[M], nxtg[M], cntg;
int headv[N], tov[M], nxtv[M], cntv;

int dfn[N], timer, st[N * 2][20], lg[N * 2], dep[N], first_pos[N], tot_dfn;
void dfs_lca(int u, int f, int d) {
    dfn[u] = ++timer;
    dep[u] = d;
    st[++tot_dfn][0] = u;
    first_pos[u] = tot_dfn;
    for (int i = headg[u]; i; i = nxtg[i]) {
        int v = tog[i];
        if (v == f) continue;
        dfs_lca(v, u, d + 1);
        st[++tot_dfn][0] = u;
    }
}
void build_st() {
    for (int i = 2; i <= tot_dfn; i++) lg[i] = lg[i >> 1] + 1;
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= tot_dfn; i++) {
            int u = st[i][j - 1], v = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = dep[u] < dep[v] ? u : v;
        }
}

inline int get_lca(int u, int v) {
    int l = first_pos[u], r = first_pos[v];
    if (l > r) swap(l, r);
    int k = lg[r - l + 1];
    int x = st[l][k], y = st[r - (1 << k) + 1][k];
    return dep[x] < dep[y] ? x : y;
}

int nodes[N * 2], k_cnt, stk[N], top;
void addEdgeG(int u, int v) {
    tog[++cntg] = v; nxtg[cntg] = headg[u]; headg[u] = cntg;
}
void addEdgeV(int u, int v) {
    if (u == v) return;
    tov[++cntv] = v; nxtv[cntv] = headv[u]; headv[u] = cntv;
    tov[++cntv] = u; nxtv[cntv] = headv[v]; headv[v] = cntv;
}

bool cmp(int a, int b) { return dfn[a] < dfn[b]; }

int clear_list[N * 2], clear_cnt;

void build_vt(int k) {
    sort(nodes + 1, nodes + 1 + k, cmp);
    top = 0; cntv = 0; clear_cnt = 0;
    if (nodes[1] != 1) stk[++top] = 1, clear_list[++clear_cnt] = 1;
    
    for (int i = 1; i <= k; i++) {
        clear_list[++clear_cnt] = nodes[i];
        if (top == 0) { stk[++top] = nodes[i]; continue; }
        int lca = get_lca(stk[top], nodes[i]);
        if (lca != stk[top]) {
            while (top > 1 && dfn[stk[top - 1]] >= dfn[lca]) {
                addEdgeV(stk[top - 1], stk[top]);
                top--;
            }
            if (stk[top] != lca) {
                clear_list[++clear_cnt] = lca;
                addEdgeV(lca, stk[top]);
                stk[top] = lca;
            }
        }
        stk[++top] = nodes[i];
    }
    while (top > 1) {
        addEdgeV(stk[top - 1], stk[top]);
        top--;
    }
}

int minT[N], minID[N], v_speed[N];
bool vis[N];
struct Node {
    int id, t, d, u;
    bool operator>(const Node& o) const {
        return t != o.t ? t > o.t : id > o.id;
    }
};
priority_queue<Node, vector<Node>, greater<Node>> pq;

void solve() {
    n = read();
    for (int i = 1; i < n; i++) {
        int u = read(), v = read();
        addEdgeG(u, v); addEdgeG(v, u);
    }
    dfs_lca(1, 0, 0);
    build_st();

    q_num = read();
    while (q_num--) {
        int s = read(), t = read();
        k_cnt = 0;
        vector<pair<int, int>> virus(s + 1);
        for (int i = 1; i <= s; i++) {
            virus[i].first = read();
            v_speed[i] = read();
            nodes[++k_cnt] = virus[i].first;
        }
        vector<int> queries(t + 1);
        for (int i = 1; i <= t; i++) {
            queries[i] = read();
            nodes[++k_cnt] = queries[i];
        }

        build_vt(k_cnt);

        for (int i = 1; i <= clear_cnt; i++) {
            int u = clear_list[i];
            minT[u] = INF; minID[u] = -1; vis[u] = false;
        }

        while (!pq.empty()) pq.pop();
        for (int i = 1; i <= s; i++) {
            int u = virus[i].first;
            minT[u] = 0; minID[u] = i;
            pq.push({i, 0, 0, u});
        }

        while (!pq.empty()) {
            Node curr = pq.top(); pq.pop();
            if (vis[curr.u]) continue;
            vis[curr.u] = true;

            for (int i = headv[curr.u]; i; i = nxtv[i]) {
                int v = tov[i];
                if (vis[v]) continue;
                int dist = curr.d + abs(dep[curr.u] - dep[v]);
                int arrival = (dist + v_speed[curr.id] - 1) / v_speed[curr.id];
                if (arrival < minT[v] || (arrival == minT[v] && curr.id < minID[v])) {
                    minT[v] = arrival;
                    minID[v] = curr.id;
                    pq.push({curr.id, arrival, dist, v});
                }
            }
        }

        for (int i = 1; i <= t; i++) printf("%d%c", minID[queries[i]], i == t ? '\n' : ' ');

        for (int i = 1; i <= clear_cnt; i++) headv[clear_list[i]] = 0;
    }
}

int main() {
    solve();
    return 0;
}