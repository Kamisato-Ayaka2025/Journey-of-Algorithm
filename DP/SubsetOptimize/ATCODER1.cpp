#include <iostream>
#include <bitset>

using namespace std;

const int N = 2e3 + 10;
int n;
int a[N] , sum;

bitset<N * N> f;

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
        sum += a[i];
    }

    f[0] = 1;
    for(int i = 1 ; i <= n ; i++){
        f |= (f << a[i]);
    }

    for(int i = (sum + 1) / 2 ; i <= sum ; i++){
        if(f[i]){
            cout << i << "\n";
            return;
        }
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

    solve();

    return 0;
}