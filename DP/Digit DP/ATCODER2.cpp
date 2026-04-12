#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;


int s;
vector<int> digit;
LL f[20][127][127][2];

LL dfs(int pos , int cur_s , int cur_v , bool limit)
{
    if(pos == (int)digit.size()){
        return (LL)(cur_s == s && cur_v == 0);
    }

    if(f[pos][cur_s][cur_v][limit] != -1){
        return f[pos][cur_s][cur_v][limit];
    }

    LL res = 0;
    int up = limit ? digit[pos] : 9;
    for(int i = 0 ; i <= up ; i++)
    {
        res += dfs(pos + 1 , cur_s + i , (cur_v * 10 + i) % s , limit && (i == up));
    }
    return f[pos][cur_s][cur_v][limit] = res;
}

void solve()
{
    LL num;
    cin >> num;
    while(num)
    {
        digit.push_back(num % 10);
        num /= 10;
    }
    reverse(digit.begin() , digit.end());

    LL res = 0;
    for( s = 1 ; s <= 126 ; s++)
    {
        //Clear
        for(int i = 0 ; i < 20 ; i++){
            for(int j = 0 ; j < 127 ; j++){
                for(int t = 0 ; t < 127 ; t++){
                    f[i][j][t][0] = f[i][j][t][1] = -1;
                }
            }
        }
    
        res += dfs(0 , 0 , 0 , true);
    }
    cout << res << "\n"; 
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