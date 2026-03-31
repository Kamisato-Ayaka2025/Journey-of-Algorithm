#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int N = 110;
const int B = 60;

vector<int> adj[N];   
int match[B];       
bool vis[B];        

bool dfs(int u) {
    for (int v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void solve() {
    int n;
    cin >> n;

    // clear
    for (int i = 0; i < n; i++) adj[i].clear();
    memset(match, -1, sizeof(match));

    for (int i = 0; i < n; i++) {
        long long x; 
        cin >> x; 
        
        for (int j = 0; j < B; j++) {
            if ((x >> j) & 1) {
                // 不用分割开，是因为adj[u] , u永远代表左侧点，而v永远是右侧点
                // 并且match , vis也都是针对右侧点的
                adj[i].push_back(j);
            }
        }
    }

    int max_matching = 0;
    for (int i = 0; i < n; i++) {
        memset(vis, false, sizeof(vis));
        if (dfs(i)) {
            max_matching++;
        }
    }

    cout << n - max_matching << endl;
}

// #define _DEBUG
int main() {
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}