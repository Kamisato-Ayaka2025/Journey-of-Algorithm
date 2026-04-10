#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

typedef long long LL;

const int mod = 1e9 + 7 , N = 1e4 + 10;

int D;
vector<int> digit;
int f[N][110][2];

int dfs(int pos , int rem , int limit)
{
    if(pos == digit.size()){
        return (rem == 0);
    }
    if(f[pos][rem][limit] != -1) return f[pos][rem][limit];

    int res = 0;
    int up = limit ? digit[pos] : 9;
    for(int i = 0 ; i <= up ; i++)
    {
        res = ((LL)res + dfs(pos + 1 , (rem + i) % D , limit && (i == up))) % mod;
    }
    return f[pos][rem][limit] = res;
}

void solve()
{
    memset(f , -1 , sizeof f);
    string num;
    cin >> num;
    cin >> D;

    int len = num.size();
    for(int i = 0 ; i < len ; i++)
    {
        int a = num[i] - '0';
        digit.push_back(a);
    }
    cout << (dfs(0 , 0 , true) - 1 + mod) % mod << "\n";
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