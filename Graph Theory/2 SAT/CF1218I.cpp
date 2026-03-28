#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int N = 2e3 + 10 , M = N * 4 + 10;
int n;
char mp[N][N] , mp1[N][N]; // 起始与结束
char B[N];

vector<int> g[M];

int dfn[M] , low[M] , timer;
stack<int> stk;
bool in_stk[M];
int id[M] , comp_cnt;

int get_val(int x , int val )
{   // 暂时这么写
    return x * 2 + val;
}

void addEdge_Same(int u , int v)
{
    g[get_val(u , 0)].push_back(get_val(v , 0));
    g[get_val(u , 1)].push_back(get_val(v , 1));
    g[get_val(v , 0)].push_back(get_val(u , 0));
    g[get_val(v , 1)].push_back(get_val(u , 1));
}

void addEdge_Diff(int u , int v)
{
    g[get_val(u , 0)].push_back(get_val(v , 1));
    g[get_val(u , 1)].push_back(get_val(v , 0));
    g[get_val(v , 0)].push_back(get_val(u , 1));
    g[get_val(v , 1)].push_back(get_val(u , 0));
}

void add_must(int u, int val) {
    if (val == 1) {
        // 选 0 则推导出 1 (矛盾)，所以必选 1
        g[get_val(u, 0)].push_back(get_val(u, 1));
    } else {
        // 选 1 则推导出 0 (矛盾)，所以必选 0
        g[get_val(u, 1)].push_back(get_val(u, 0));
    }
}

void dfs(int u)
{
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    in_stk[u] = true;
    
    for(int v : g[u])
    {
        if(!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u] , low[v]);
        }
        else if(in_stk[v])
        {
            low[u] = min(low[u] , dfn[v]);
        }
    }

    if(dfn[u] == low[u])
    {
        comp_cnt++;
        while(true)
        {
            int node = stk.top();
            stk.pop();
            in_stk[node] = false;

            id[node] = comp_cnt;
            if(node == u) break;
        }
    }
}

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> mp[i] + 1;
    }
    for(int i = 1 ; i <= n ; i++){
        cin >> mp1[i] + 1;
    }
    cin >> B + 1;

   for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int diff = (mp[i][j] != mp1[i][j]);
            int bi = B[i] - '0', bj = B[j] - '0';
            int row = i, col = n + j;

            if (bi == 0 && bj == 0) {
                if (diff == 1) { cout << -1 << "\n"; return; }
            } 
            else if (bi == 0 && bj == 1) {
                add_must(row, diff); 
            } 
            else if (bi == 1 && bj == 0) {
                add_must(col, diff); 
            } 
            else { 
                if (diff == 0) addEdge_Same(row, col);
                else addEdge_Diff(row, col);
            }
        }
    }

    for(int i = 2 ; i <= 4 * n + 1 ; i++){
        if(!dfn[i]) dfs(i);
    }

    for(int i = 1 ; i <= 2 * n ; i++){
        if(id[get_val(i , 0)] == id[get_val(i , 1)]){
            cout << -1 << "\n";
            return;
        }
    }

    // 输出方案
    vector<int> result_row , result_col;
    for(int i = 1 ; i <= n ; i++){
        // 先看行
        if(id[get_val(i , 0)] > id[get_val(i , 1)]){
            result_row.push_back(i - 1);
        }
    }

    for(int i = n + 1 ; i <= 2 * n ; i++){
        // 再看列
        if(id[get_val(i , 0)] > id[get_val(i , 1)]){
            result_col.push_back(i - n - 1);
        }
    }

    cout << (int)result_row.size() + (int)result_col.size() << "\n";
    for(int i : result_row){
        cout << "row " << i << "\n";
    }
    for(int i : result_col){
        cout << "col " << i << "\n";
    }
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" , "w" , stdout );
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}