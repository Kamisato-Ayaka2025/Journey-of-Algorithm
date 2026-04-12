#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const int mod = 998244353;
typedef long long LL;

class Node{
public:
    LL cnt , sum ;
    Node() : cnt(-1) , sum(-1) {};
    Node(LL c , LL s) : cnt(c) , sum(s) {};
};

int k;
LL l , r;
Node f[20][2][2][1 << 10];
vector<int> digit;
LL pw[20];

inline int used(int num)
{
    int res = 0;
    for(int i = 0 ; i < 10 ; i++){
        if(num >> i & 1){
            res++;
        }
    }
    return res;
}

Node dfs(int pos , int lead , int limit , int mask)
{
    if(used(mask) > k){ // 不合法的情况
        return Node(0 , 0);
    }

    if(pos == (int)digit.size())
    {
        return Node(1 , 0);
    }

    if(f[pos][lead][limit][mask].cnt != -1){
        return f[pos][lead][limit][mask];
    }

    LL res = 0 , cnt = 0;
    int up = limit ? digit[pos] : 9;
    for(int i = 0 ; i <= up ; i++)
    {
        Node tmp = dfs(pos + 1 , lead && (i == 0) , limit && (i == up) , lead && (i == 0) ? mask : mask | (1 << i));
        res = (res + tmp.cnt % mod * i % mod * pw[(int)digit.size() - pos - 1] % mod) % mod;
        res = (res + tmp.sum) % mod;
        cnt = cnt + tmp.cnt;
    }

    f[pos][lead][limit][mask] = Node(cnt , res);
    return f[pos][lead][limit][mask];
}

LL calc(LL num)
{
    for(int i = 0 ; i < 20 ; i++){
        for(int j = 0 ; j < 2 ; j++){
            for(int s = 0 ; s < 2 ; s++){
                for(int t = 0 ; t < (1 << 10) ; t++){
                    f[i][j][s][t] = Node(-1 , -1);
                }
            }
        }
    }
    digit.clear();
    while(num)
    {
        digit.push_back(num % 10);
        num /= 10;
    }
    reverse(digit.begin() , digit.end());
    return dfs(0 , true , true , 0).sum % mod;
}

void solve()
{
    pw[0] = 1;
    for(int i = 1 ; i < 20 ; i++){
        pw[i] = pw[i - 1] * 10ll % mod;
    }

    cin >> l >> r >> k;
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