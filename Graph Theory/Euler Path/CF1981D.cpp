#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_M = 1500;
const int MAX_P = 300000;

int primes[MAX_M + 10];
bool is_prime[MAX_P + 10];
bool vis[MAX_M + 5][MAX_M + 5];
int cur_edge[MAX_M + 5]; 
vector<int> res_path;

void sieve() {
    fill(is_prime + 2, is_prime + MAX_P, true);
    int cnt = 0;
    for (int i = 2; i < MAX_P && cnt < MAX_M; i++) {
        if (is_prime[i]) {
            primes[cnt++] = i;
            for (long long j = 1LL * i * i; j < MAX_P; j += i)
                is_prime[j] = false;
        }
    }
}

long long get_max_edges(int m) {
    if (m % 2 != 0) return 1LL * m * (m + 1) / 2;
    return 1LL * m * m / 2 + 1;
}

inline bool has_edge(int u, int v, int m) {
    if (m % 2 != 0) return true;
    if (u > v) swap(u, v);
    if (u > 1 && u % 2 == 0 && v == u + 1 && v < m) return false;
    return true;
}

void dfs(int u, int m) {
    for (int &v = cur_edge[u]; v <= m; ) {
        int next_v = v++; 
        if (!vis[u][next_v] && has_edge(u, next_v, m)) {
            vis[u][next_v] = vis[next_v][u] = true;
            dfs(next_v, m);
        }
    }

    res_path.push_back(primes[u - 1]);
}

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << primes[0] << "\n";
        return;
    }

    int l = 1, r = MAX_M, m = MAX_M;
    while (l < r) {
        int mid = (l + r) / 2;
        if (get_max_edges(mid) >= n - 1) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    m = l;
    // Clear
    for (int i = 1; i <= m; i++) {
        cur_edge[i] = 1;
        for (int j = 1; j <= m; j++) vis[i][j] = false;
    }
    res_path.clear();

    dfs(1, m);

    for (int i = 0; i < n; i++) {
        cout << res_path[i] <<  " ";
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

    sieve();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}