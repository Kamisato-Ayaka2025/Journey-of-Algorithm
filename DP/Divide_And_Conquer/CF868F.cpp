#include <iostream>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

LL dp[25][N];

int n , k;
int a[N];
int curR , curL , cnt[N];
LL curAns;

void get_cost(int L , int R)
{
    while(curR < R)
    {
        curR++;
        curAns += cnt[a[curR]];
        cnt[a[curR]]++;
    }

    while(curL > L)
    {
        curL--;
        curAns += cnt[a[curL]];
        cnt[a[curL]]++;
    }

    while(curR > R)
    {
        cnt[a[curR]]--;
        curAns -= cnt[a[curR]];
        curR--;
    }

    while(curL < L)
    {
        cnt[a[curL]]--;
        curAns -= cnt[a[curL]];
        curL++;
    }
}

void compute(int cnt , int l , int r , int optl , int optr)
{
    if(l > r) return;

    int mid = (l + r) >> 1;
    int opt = -1;
    dp[cnt][mid] = 1E18;
    for(int i = optl ; i <= min(mid , optr) ; i++)
    {
        get_cost(i , mid);
        if(dp[cnt][mid] > dp[cnt - 1][i - 1] + curAns)
        {
            dp[cnt][mid] = dp[cnt - 1][i - 1] + curAns;
            opt = i;
        }
    }

    compute(cnt , l , mid - 1 , optl , opt);
    compute(cnt , mid + 1 , r , opt , optr);
}

void solve()
{
    curL = 1 , curR = 0 , curAns = 0;

    cin >> n >> k;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> a[i];
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