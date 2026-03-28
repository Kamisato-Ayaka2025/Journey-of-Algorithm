#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef pair<int , int> PII;

const int N = 1e5 + 10;

int n , m;

void solve()
{
    cin >> n >> m;

    map<pair<int , int> , bool> mp;
    vector<int> ans;

    for(int i = 1 ; i <= m ; i++)
    {
        int u , v;
        cin >> u >> v;
        mp[{u , v}] = true;
    }

    int sz = 0;
    for(int i = 1 ; i <= n  ;i++)
    {
        ans.push_back(i);
        sz++;
        for(int j = sz - 1 ; j >= 1 ; j--){
            if(mp[{ans[j - 1] ,ans[j]}]){
                swap(ans[j] , ans[j - 1]);
            }
            else break;
        }
    }

    for(auto v : ans){
        cout << v << " ";
    }
    cout << "\n";
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
    while( T-- ) solve();
    return 0;
}