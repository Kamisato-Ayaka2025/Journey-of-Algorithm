#include <iostream>

using namespace std;

const int N = 4e4;
int a[N];
int n , k;
// 表示考虑前 i 个元素，分成 j 个盒子的最大贡献
// dp[i][j] = min(dp[k - 1][j - 1] + C(k , j));
int dp[2][N];

int curL , curR , cnt[N] , curAns;
inline int get_cost(int L , int R)
{
    // 区间扩展
    while(curR < R)
    {
        int val = a[++curR];
        if(++cnt[val] == 1) curAns++;
    }

    while(curL > L)
    {
        int val = a[--curL];
        if(++cnt[val] == 1) curAns++;
    }

    // 区间收缩
    while(curR > R)
    {
        int val = a[curR--];
        if(--cnt[val] == 0) curAns--; 
    }
    while(curL < L)
    {
        int val = a[curL++];
        if(--cnt[val] == 0) curAns--;
    }
    return curAns;
}

void compute(int cnt , int l , int r , int optl , int optr)
{
    if(l > r) return;

    int mid = (l + r) >> 1;
    pair<int , int> best = {-2e9 , -1};
    for(int i = optl ; i <= min(optr , mid) ; i++)
    {
        best = max(best , {dp[(cnt - 1) & 1][i - 1] + get_cost(i , mid) , i});
    }

    dp[cnt & 1][mid] = best.first;
    int opt = best.second;

    compute(cnt , l , mid - 1 , optl , opt);
    compute(cnt , mid + 1 , r , opt , optr);
}

void solve()
{
    curL = 1 , curR = 0; // init

    cin >> n >> k;
    for(int i = 1 ; i <= n;  i++)
    {
        cin >> a[i];
    }

    for(int i = 1 ; i <= n ; i++)
    {
        dp[1][i] = get_cost(1 , i);
    }

    for(int i = 2 ; i <= k ; i++)
    {
        compute(i , 1 , n , 1 , n);
    }

    cout << dp[k & 1][n] << "\n";
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