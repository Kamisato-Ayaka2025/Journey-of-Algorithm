#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long LL;

const int mod = 1e9 + 7;

int n;
LL l , r , z;
LL f[62][2010];

LL comb[1005][1005];

void precompute_C() {
    for (int i = 0; i <= 1000; i++) {
        comb[i][0] = 1; 
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
        }
    }
}

LL C(int n, int i) {
    if (i < 0 || i > n) return 0;
    return comb[n][i];
}

LL dfs(int pos, LL R, int rem) {
    if (pos == -1) return 1;

    int memo_rem = min(rem, 2000); 
    if (f[pos][memo_rem] != -1) return f[pos][memo_rem];

    LL res = 0;
    int bit_R = (R >> pos) & 1;
    int bit_Z = (z >> pos) & 1;

    LL up = min((LL)2000, (LL)rem * 2 + bit_R);

    for (int i = bit_Z; i <= n && i <= up; i += 2) {
        LL next_rem = up - i;
        res = (res + C(n, i) * dfs(pos - 1, R, (int)next_rem)) % mod;
    }

    return f[pos][memo_rem] = res;
}

LL calc(LL num)
{
    for(int i = 0 ; i < 62 ; i++){
        for(int j = 0 ; j < 2010 ; j++){
            f[i][j] = -1;
        }
    }

    return dfs(61 , num , 0);
}

void solve()
{
    precompute_C();
    cin >> n >>  l >> r >> z;
    cout << (calc(r) - calc(l - 1) + mod) % mod << "\n";
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