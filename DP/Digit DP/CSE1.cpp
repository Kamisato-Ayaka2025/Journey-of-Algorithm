#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;
LL f[20][11][2][2];
vector<int> digit;
LL dfs(int pos , int pre , int lead , int limit)
{   // 目前进行到的数位 前一位 是否为前导 是否有上限
    if(pos == digit.size()) return 1;
    if(f[pos][pre][lead][limit] != -1) return f[pos][pre][lead][limit];

    LL res = 0;
    int up = limit ? digit[pos] : 9;
    for(int i = 0 ; i <= up ; i++)
    {
        if(!lead && i == pre) continue;
        res += dfs(pos + 1 , i , lead && (i == 0) , limit && (i == up));
    }
    return f[pos][pre][lead][limit] = res;
}

LL calc(LL num)
{
    digit.clear();
    for(int i = 0 ; i < 20 ; i++){
        for(int j = 0 ; j < 11 ; j++){
            f[i][j][0][0] = f[i][j][0][1] = f[i][j][1][0] = f[i][j][1][1] = -1;
        }
    }

    while(num){
        digit.push_back(num % 10);
        num /= 10;
    }
    reverse(digit.begin() , digit.end());
    return dfs(0 , 0 , true , true);
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

    solve();
    return 0;
}