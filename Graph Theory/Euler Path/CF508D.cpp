#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 62 * 62 + 10;
vector<int> g[N];
vector<int> path;
int out[N] , in[N];
int n;

// 哈希
int getNum(char c)
{   // from 0 to 61
    if(c >= '0' && c <= '9') return c - '0';
    if(c >= 'a' && c <= 'z') return c - 'a' + 10;
    if(c >= 'A' && c <= 'Z') return c - 'A' + 36;
    return -1; // error
}

char getChar(int i)
{
    if(i < 10) return (char)('0' + i);
    if(i < 36) return (char)('a' + i - 10);
    return (char)('A' + i - 36);
}

void dfs(int u)
{
    while(!g[u].empty())
    {
        int v = g[u].back();
        g[u].pop_back();
        dfs(v);
    }
    path.push_back(u);
}

void solve()
{   
    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
        string s;
        cin >> s;
        int u = getNum(s[0]) * 62 + getNum(s[1]);
        int v = getNum(s[1]) * 62 + getNum(s[2]);

        g[u].push_back(v);
        out[u]++;
        in[v]++;
    }

    bool ok = true;
    int start_node = -1;
    int end_node = -1;
    int start_count = 0;
    int end_count = 0;
    for(int i = 0 ; i < N ; i++)
    {
        if(in[i] == out[i]) continue;
        if(out[i] == in[i] + 1){
            start_count++;
            start_node = i;
        }
        else if(in[i] == out[i] + 1){
            end_count++;
            end_node = i;
        }
        else{
            ok = false;
        }
    }

    if(!ok || start_count > 1 || end_count > 1){
        cout << "NO\n";
        return;
    }

    if(start_node == -1){
        for(int i = 0 ; i < N ; i++){
            if(out[i] > 0){
                start_node = i;
            }
        }
    }

    if(start_node != -1){
        dfs(start_node);
    }

    if((int)path.size() != n + 1){
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
        reverse(path.begin() , path.end());
        string res = "";

        res += getChar(path[0] / 62);
        res += getChar(path[0] % 62);

        for(int i = 1 ; i < (int)path.size() ; i++)
        {
            res += getChar(path[i] % 62);
        }
        cout << res << "\n";
    }
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt"  ,"w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}