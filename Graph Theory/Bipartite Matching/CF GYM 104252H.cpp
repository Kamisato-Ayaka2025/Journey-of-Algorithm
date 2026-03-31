#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cstring>

using namespace std;

// 快速名字映射：3字母小写 -> 27^3 空间
inline int name_to_hash(const string& s) {
    int h = 0;
    for (char c : s) h = h * 27 + (c - 'a' + 1);
    return h;
}

int name_id[20000]; // 存储名字哈希对应的马 ID
string id_to_name[305];
bitset<305> can[305];
bitset<305> forbidden_for_rank_below[305];

int match[305]; // 马匹配的名次
int horse_at_rank[305]; // 名次匹配的马
bool vis[305];
vector<int> adj[305];

bool dfs(int u) {
    for (int v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (horse_at_rank[v] == -1 || dfs(horse_at_rank[v])) {
                horse_at_rank[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    // 极致流优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        id_to_name[i] = s;
        name_id[name_to_hash(s)] = i;
        can[i + 1].set(); // 1-indexed ranks, 初始化所有名次都可能是任何马
    }

    int r_cnt;
    cin >> r_cnt;
    while (r_cnt--) {
        int m, w;
        cin >> m >> w;
        bitset<305> current_h;
        for (int i = 0; i < m; i++) {
            string s;
            cin >> s;
            current_h.set(name_id[name_to_hash(s)]);
        }
        // 规则1：第 w 名必在当前集合中
        can[w] &= current_h;
        // 规则2：当前集合中的马排名必不小于 w
        if (w > 1) {
            forbidden_for_rank_below[w - 1] |= current_h;
        }
    }

    // 传递禁位：如果马不能是第 W 名，它也不能是第 W-1, W-2... 名
    for (int i = n - 1; i >= 1; i--) {
        forbidden_for_rank_below[i] |= forbidden_for_rank_below[i + 1];
    }
    for (int i = 1; i <= n; i++) {
        can[i] &= ~forbidden_for_rank_below[i];
    }

    // 建图
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            if (can[i].test(j)) {
                adj[i].push_back(j);
            }
        }
    }

    // 匹配
    memset(horse_at_rank, -1, sizeof(horse_at_rank));
    for (int i = 1; i <= n; i++) {
        memset(vis, false, sizeof(vis));
        dfs(i);
    }

    // 结果反查并输出
    vector<string> res(n + 1);
    for (int j = 0; j < n; j++) {
        if (horse_at_rank[j] != -1) {
            res[horse_at_rank[j]] = id_to_name[j];
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << res[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}