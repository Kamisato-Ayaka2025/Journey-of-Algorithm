#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int N = 5e3 + 10;

int n;
vector<int> g[N];
stack<int> stk;

int dfn[N] , low[N] , timer;
int id[N] , comp_cnt;
bool in_stk[N];

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

inline int get_id(int idx , int val)
{
    return idx * 2 + val;
}

void add_same(int x , int y)
{   // 第 x 行与第 y 列
    g[get_id(x , 0)].push_back(get_id(y , 0));
    g[get_id(y , 0)].push_back(get_id(x , 0));

    g[get_id(x , 1)].push_back(get_id(y , 1));
    g[get_id(y , 1)].push_back(get_id(x , 1));
}

void add_diff(int x , int y)
{   // 第 x 行与第 y 列
    g[get_id(x , 0)].push_back(get_id(y , 1));
    g[get_id(y , 1)].push_back(get_id(x , 0));

    g[get_id(x , 1)].push_back(get_id(y , 0));
    g[get_id(y , 0)].push_back(get_id(x , 1));
}

void solve()
{
    cin >> n;
    vector<string> a(n + 1) , b(n + 1);
    
    for(int i = 1 ; i <= n ; i++) cin >> a[i];
    for(int i = 1 ; i <= n ; i++) cin >> b[i];

    // init
    for(int i = 1 ; i <= 2 * n ; i++)
    {
        g[get_id(i , 0)].clear();
        g[get_id(i , 1)].clear();
        dfn[get_id(i , 0)] = dfn[get_id(i , 1)] = low[get_id(i , 0)] = low[get_id(i , 1)] = 0;
        in_stk[get_id(i , 0)] = in_stk[get_id(i , 1)] = false;
        timer = comp_cnt = 0;
    }

    // build graph
    for(int i = 1 ; i <= n ; i++){
        for(int j = 0 ; j < n ; j++){
            char num1 = a[i][j] , num2 = b[i][j];
            if(num1 == num2) add_same(i , j + 1 + n);
            else{
                add_diff(i , j + 1 + n);
            }
        }
    }

    for(int i = 2 ; i <= 4 * n + 1 ; i++)
    {
        if(!dfn[i]) dfs(i);
    }

    bool ok = true;
    for(int i = 1 ; i <= 2 * n ; i++)
    {
        if(id[get_id(i , 0)] == id[get_id(i , 1)])
        {
            ok = false;
            break;
        }
    }

    if(ok) cout << "YES\n";
    else cout << "NO\n";
    return;
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
    }
    return 0;
}