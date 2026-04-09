#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
typedef long long LL;
const int N = 2e3 + 10 , M = 3e6 + 6e5 + 10;
int n;
int A , B;
int D[N];
LL sum_d;

bitset<M> dp[N]; 

vector<bool> trace_back(int target)
{
    vector<bool> used(n + 1,  false);
    int cur = target;
    for(int i = n ; i >= 1 ; i--)
    {
        if(cur >= D[i] && dp[i - 1][cur - D[i]]){
            cur -= D[i];
            used[i] = true;
        }
    }
    return used;
}

void solve()
{
    cin >> n >> A >> B;
    for(int i = 1 ; i <= n ; i++){
        cin >> D[i];
        sum_d += D[i];
    }

    LL U1 = A + B , U2 = A - B;
    if(((U1  + sum_d) % 2) || ((U2 + sum_d)% 2) || (abs(U1) > sum_d) || (abs(U2) > sum_d)){
        cout << "No\n";
        return;
    }  

    int target_u1 = (U1 + sum_d) / 2;
    int target_u2 = (U2 + sum_d) / 2;

    dp[0][0] = 1;
    for(int i = 1 ; i <= n ; i++)
    {
        dp[i] = dp[i - 1] | (dp[i - 1] << D[i]);
    }

    if(!dp[n][target_u1] || !dp[n][target_u2]){
        cout << "No\n";
        return;
    }

    vector<bool> used_u1 = trace_back(target_u1); 
    vector<bool> used_u2 = trace_back(target_u2);

    string res = "";
    for(int i = 1 ; i <= n ; i++)
    {
        if (used_u1[i] && used_u2[i]) res += 'R';
        else if (!used_u1[i] && !used_u2[i]) res += 'L';
        else if (used_u1[i] && !used_u2[i]) res += 'U';
        else res += 'D';
    }
    cout << "Yes\n";
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