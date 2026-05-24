#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 35010;

int n , k;
int a[N] , last_pos[N] , pre[N] , nxt[N];
int dp[110][N]; 

int curL , curR , curAns;

inline void get_cost(int L , int R)
{
    while(curR < R)
    {   
        curR++;
        if(pre[curR] >= curL) curAns += curR - pre[curR];
    }

    while(curL > L)
    {   
        curL--;
        if(nxt[curL] && nxt[curL] <= curR) curAns += nxt[curL] - curL;
    }

    while(curR > R)
    {  
        if(pre[curR] >= curL) curAns -= curR - pre[curR];
        curR--;
    }   

    while(curL < L)
    {   
        if(nxt[curL] && nxt[curL] <= curR) curAns -= nxt[curL] - curL;
        curL++;
    }
}

void compute(int cnt , int l , int r , int optl , int optr)
{
    if(l > r) return;
    int mid = (l + r) >> 1;

    int opt = optl;
    dp[cnt][mid] = 0x3f3f3f3f;

    for(int i = optl ; i <= min(mid , optr) ; i++)
    {
        get_cost(i , mid);
        if(dp[cnt][mid] > dp[cnt - 1][i - 1] + curAns)
        {
            dp[cnt][mid] = dp[cnt - 1][i - 1] + curAns;
            opt = i;
        }
    }

    compute(cnt , l , mid  - 1, optl , opt);
    compute(cnt , mid + 1 , r , opt , optr);
}

void solve()
{
    // memset(dp , 0x3f , sizeof dp);
    curL = 1; curR = 0; curAns = 0; 

    cin >> n >> k;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> a[i];
        pre[i] = last_pos[a[i]];
        if(pre[i]) nxt[pre[i]] = i;
        last_pos[a[i]] = i;
    }

    for(int i = 1 ; i <= n ; i++)
    {
        get_cost(1 , i);
        dp[1][i] = curAns;
    }

    for(int i = 2 ; i <= k ; i++)
    {
        compute(i , 1 , n , 1 , n);
    }

    cout << dp[k][n] << "\n";
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

    solve();

    return 0;
}