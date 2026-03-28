#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 310;
int dist[N][N];
int n;

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            cin >> dist[i][j];
        }
    }

    int k;
    cin >> k;
    for(int t = 1 ; t <= k ; t++)
    {
        LL sum = 0;
        int a , b , c;
        cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = min(dist[a][b] , c);

        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= n ; j++){
                dist[i][j] = min(dist[i][j] , dist[i][a] + dist[b][j] + dist[a][b]);
                dist[i][j] = min(dist[i][j] , dist[i][b] + dist[a][j] + dist[a][b]);
                sum += dist[i][j];
            }
        }
        cout << sum / 2 << " ";
    }
    return;
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt" , "w"  ,stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}