#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

LL f[20][4][2];
vector<int> digit;
LL dfs(int pos , int rem , int limit)
{
    if(pos == digit.size()){
        return 1;
    }
    if(f[pos][rem][limit] != -1) return f[pos][rem][limit];

    LL res = 0;
    int up = limit ? digit[pos] : 9;
    for(int i = 0 ; i <= up ; i++)
    {
        if(i == 0){
            res += dfs(pos + 1 , rem , limit && (i == up));
        }
        else{
            if(rem == 0) break;
            res += dfs(pos + 1 , rem - 1, limit && (i == up));
        }
    }
    return f[pos][rem][limit] = res;
}

LL calc(LL num)
{
    digit.clear();
    for(int i = 0 ; i < 20 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            f[i][j][0] = f[i][j][1] = -1;
        }
    }

    while(num)
    {
        digit.push_back(num % 10);
        num /= 10;
    }
    reverse(digit.begin() , digit.end());
    return dfs(0 , 3 , true);
}

void solve()
{
    LL a , b;
    cin >> a >> b;
    cout << calc(b) - calc(a - 1) << "\n";
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
    while( T-- ){
        solve();
    }
    return 0;
}