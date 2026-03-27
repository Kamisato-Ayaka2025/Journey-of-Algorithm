#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int N = 510 , M = N * 2 + 10;
int n;
vector<int> table[3];

vector<int> g[M];

int dfn[M] , low[M] , timer;
stack<int> stk;
bool in_stk[M];
int id[M] , comp_cnt;

inline int get_val(int x , int val)
{
    return 2 * abs(x) + (x > 0 ? val : val ^ 1);
}

void addEdge_Diff(int a , int b)
{
    g[get_val(a , 1)].push_back(get_val(b , 0));
}

void addEdge_inline(int a , int b , int c)
{   // a == -1 -> b == 1 && c == 1
    addEdge_Diff(a , b);
    addEdge_Diff(a , c);
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

    if(low[u] == dfn[u])
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
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 1 ; j <= n ; j++){
            int x; cin >> x;
            table[i].push_back(x);
        }
    }

    for(int j = 0 ; j < n ; j++)
    {
        int a = table[0][j] , b = table[1][j] , c = table[2][j];

        addEdge_inline(a , b , c);
        addEdge_inline(b , a , c);
        addEdge_inline(c , a , b);
    }

    for(int i = 2 ; i <= 2 * n + 1 ; i++){
        if(!dfn[i]) dfs(i);
    }

    for(int i = 1 ; i <= n ; i++){
        if(id[get_val(i , 0)] == id[get_val(i , 1)]){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    return;
}

void clear()
{
    //CLEAR
    for(int i = 0 ; i < 3 ; i++){
        table[i].clear();
    }

    for(int i = 0 ; i <= 2 * n + 1 ; i++){
        g[i].clear();
        dfn[i] = low[i] = id[i] = 0;
        in_stk[i] = false;
    }
    timer = comp_cnt = 0;
    while(!stk.empty()) stk.pop();
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" , "w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while( T-- ){
        solve();
        clear();
    }
    return 0;
}   