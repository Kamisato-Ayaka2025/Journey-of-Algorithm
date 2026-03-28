#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n , m , q;
int p[N] , A[N] , B[N];
int last_val[N] , last_occur[N];
int up[N][20] , start_pos[N]; // 表示以i结尾的串的最近起始点
int start_pos_mx[N]; // 考虑从1 ~ i的序列，最靠近i的起始点是？

void solve()
{
    cin >> n >> m >> q;
    for(int i = 1 ; i <= n ; i++){
        cin >> p[i];
    }
    for(int i = 1 ; i <= m ; i++) cin >> A[i];

    // 建图
    for(int i = 1 ; i <= n ; i++)
    {
        last_val[p[i]] = p[(i - 2 + n) % n + 1];
    }

    for(int i = 1 ; i <= m ; i++)
    {
        int pre_val = last_val[A[i]];
        B[i] = last_occur[pre_val];
        last_occur[A[i]] = i;
    }

    // 利用倍增
    for(int i = 1 ; i <= m ; i++) up[i][0] = B[i];
    for(int j = 1 ; j < 20 ; j++ ){
        for(int i = 1 ; i <= m ; i++){
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    for(int i = 1 ; i <= m ; i++){
        int cur = i;
        int steps = n - 1;
        for(int j = 19 ; j >= 0 ; j--){
            if(steps & (1 << j)){
                cur = up[cur][j];
            }
        }
        start_pos[i] = cur;
    }

    // DP
    for(int i = 1 ; i <= m ; i++){
        start_pos_mx[i] = max(start_pos_mx[i - 1] , start_pos[i]);
    }
    
    while( q-- )
    {
        int l , r;
        cin >> l >> r;
        if(start_pos_mx[r] >= l){
            cout << 1;
        }
        else cout << 0;
    }
    cout << "\n";
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt"  ,"r" , stdin);
    freopen("output.txt"  ,"w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}