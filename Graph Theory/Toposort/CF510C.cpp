#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N =  110;

int n;
string name[N];
vector<int> g[28];
int in[28] , q[28] , tt , hh;

void toposort()
{
    for(int i = 1 ; i <= 26 ; i++)
    {
        if(!in[i]) q[++tt] = i;
    }

    while(hh <= tt)
    {
        int t = q[hh++];
        for(int v : g[t])
        {
            in[v]--;
            if(!in[v]) q[++tt] = v;
        }
    }
}

void solve()
{
    tt = -1 , hh = 0;

    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> name[i];
    }

    for(int i = 1 ; i < n ; i++)
    {
        bool different = false;
        int sz1 = (int)name[i].size() , sz2 = (int)name[i + 1].size();
        int ptr = 0;
        while(ptr < sz1 && ptr < sz2)
        {
            if(name[i][ptr] != name[i + 1][ptr]){
                int u = name[i][ptr] - 'a'  + 1, v = name[i + 1][ptr] - 'a' + 1;
                g[u].push_back(v);
                in[v]++;
                different = true;
                break;
            }
            ptr++;
        }

        if(!different){
            if(sz1 > sz2){
                cout << "Impossible\n";
                return;
            }
        }
    }

    toposort();
    if(tt < 25){
        cout << "Impossible\n";
    }
    else{
        for(int i = 0 ; i < 26 ; i++){
            cout << (char)('a' + q[i] - 1);
        }
        cout << "\n";
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