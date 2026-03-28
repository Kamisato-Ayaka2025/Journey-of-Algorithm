#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 510;
int n;

int dist[N][N];
int x[N];
bool added[N];
LL res[N];

void solve()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            cin >> dist[i][j];
        }
    }

    for(int i = 1 ; i <= n ; i++){
        cin >> x[i];
    }

    
    for(int k = n ; k >= 1 ; k--)
    {
        LL sum = 0;
        int curr = x[k];
        added[curr] = true;

        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= n ; j++){
                dist[i][j] = min(dist[i][j] , dist[i][curr] + dist[curr][j]);
            }
        }

        for(int i = 1 ; i <= n ; i++)
        {
            if(!added[i]) continue;
            for(int j = 1 ; j <= n ; j++)
            {
                if(!added[j]) continue;
                sum += dist[i][j];
            }
        }

        res[k] = sum;
    }

    for(int i = 1 ; i <= n ; i++)
    {
        cout << res[i] << " ";
    }
    cout << "\n";
}

// #define _DEBUG
int main()
{
#ifdef _DEBUG
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt"  ,"w" , stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}