#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int N = 4e5 + 10, M = 8e5 + 10, MAX_VAL_OFFSET = 100005;
int m;
int h[N], e[M], ne[M], idx;
int bel[M], pos[M]; 
bool used[M / 2]; 

vector<string> res;

void addEdge(int u, int v, int id, int index) {
    e[idx] = v, ne[idx] = h[u], bel[idx] = id, pos[idx] = index, h[u] = idx++;
}

void dfs(int u) {
    for (int &i = h[u]; i != -1; ) {
        int j = i;
        i = ne[i]; 
        if (used[j / 2]) continue;
        used[j / 2] = true;

        int belong = bel[j], position = pos[j];
        if (u > MAX_VAL_OFFSET) res[belong][position] = 'L';
        else res[belong][position] = 'R';

        dfs(e[j]);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    idx = 0;
    
    cin >> m;
    res.resize(m + 1);
    
    vector<vector<int>> arrays(m + 1);
    vector<int> all_nums;
    map<int, int> total_freq;

    for (int i = 1; i <= m; i++) {
        int n;
        cin >> n;
        res[i].assign(n, ' ');
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            arrays[i].push_back(x);
            all_nums.push_back(x);
            total_freq[x]++;
        }
    }

    for (auto const& [val, count] : total_freq) {
        if (count % 2 != 0) {
            cout << "NO" << endl;
            return;
        }
    }

    sort(all_nums.begin(), all_nums.end());
    all_nums.erase(unique(all_nums.begin(), all_nums.end()), all_nums.end());

    // 建图
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < (int)arrays[i].size(); j++) {
            int val = lower_bound(all_nums.begin(), all_nums.end(), arrays[i][j]) - all_nums.begin() + 1;
            int u = i + MAX_VAL_OFFSET;
            int v = val;
            addEdge(u, v, i, j);
            addEdge(v, u, i, j);
        }
    }

    for (int i = 1; i < N; i++) {
        if (h[i] != -1) {
            dfs(i);
        }
    }

    cout << "YES" << endl;
    for (int i = 1; i <= m; i++) {
        cout << res[i] << "\n";
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