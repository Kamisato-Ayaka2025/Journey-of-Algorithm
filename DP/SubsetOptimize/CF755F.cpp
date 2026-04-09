#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

const int N = 1e6 + 10;
typedef long long LL;
int n , k;

int p[N];
vector<int> cycle[N];
int cycle_cnt;
int sz[N] , sz_count[N];
bool vis[N];
int max_double;
bitset<N> f;

void solve()
{
    cin >> n >> k;
    
    for(int i = 1 ; i <= n ; i++){
        cin >> p[i];
    }

    //找环
    for(int i = 1 ; i <= n ; i++)
    {
        if(!vis[i]){
            int node = i;
            cycle_cnt++;

            while(!vis[node]){
                cycle[cycle_cnt].push_back(node);
                sz[cycle_cnt]++;
                vis[node] = true;
                node = p[node];
            }

            sz_count[sz[cycle_cnt]]++;
            max_double += sz[cycle_cnt] / 2;
        }
    }

    // 先求最大覆盖
    int res2 = 0;
    if(k <= max_double){
        res2 = k * 2;
    }
    else{
        res2 = min(n , max_double * 2 + (k - max_double));
    }

    // 然后求最小覆盖
    // 最小覆盖只有两种情况，要么刚好为k，要么就是k + 1
    f[0] = 1;
    for(int i = 1 ; i <= n ; i++)
    {
        if(sz_count[i])
        {
            int num = sz_count[i];
            for(int bit = 1 ; num ; bit <<= 1)
            {
                int use = min(bit , num);
                LL wegiht = (LL)i * use;
                f |= (f << wegiht);
                num -= use;
            }
        }
    }

    int res1 = (f[k] == 1 ? k : k + 1);
    cout << res1 << " " << res2 << "\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" ,"w",  stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}