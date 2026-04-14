#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 2e6 + 10;
int n , k;
string target , res;
int cnt0[N]; // 第 i 位上有多少个0

bool dfs(int pos , int cur , vector<vector<int>> &f)
{   // pos从低位到高位 , cur表示当前进位
    if(pos == k)
    {
        return cur == 0; // 进位必须是0
    }

    if(f[pos][cur] != -1) return f[pos][cur];

    for(int i = 0 ; i < 2 ; i++)
    {   //尝试0 和 1
        int curCost = cur + (i == 0 ? n - cnt0[pos] : cnt0[pos]);
        int curBit = curCost & 1;
        int next = curCost >> 1;

        if(curBit != (target[pos] - '0')) continue;
        
        if(dfs(pos + 1 , next , f)){
            res += (char)('0' + i);
            return true;
        }
    }
    return false;
}

void solve()
{
    cin >> n >> k;
    vector<vector<int>> f(k + 10, vector<int>(n + 10 , -1));

    cin >> target;
    reverse(target.begin() , target.end());

    for(int i = 1 ; i <= n ; i++)
    {
        string s;
        cin >> s;
        for(int j = 0 ; j < k ; j++)
        {
            int c = s[j] - '0';
            if(c == 0){
                cnt0[k - j - 1]++; // 相当于翻转
            }
        }
    }

    if(dfs(0 , 0 , f)){
        cout << res << "\n";
    }
    else{
        cout << "-1\n";
    }

    // CLEAR
    target.clear();
    res.clear();
    for(int i = 0 ; i < k ; i++)
    {
        cnt0[i] = 0;
    }
        
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
    while( T-- )
    {
        solve();
    }
    return 0;
}