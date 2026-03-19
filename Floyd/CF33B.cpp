#include <iostream>
#include <vector>

using namespace std;

#define INF 1e9

int n;
string s , t;

int dist[28][28];

void solve()
{
    cin >> s >> t;
    if((int)s.size() != (int)t.size()){
        cout << "-1\n";
        return;
    }

    for(int i = 0 ; i < 27 ; i++){
        for(int j = 0 ; j < 27 ; j++){
            if(i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
        int w;
        char a[2] , b[2];
        cin >> a >> b >> w;

        int u = a[0] - 'a' + 1 , v = b[0] - 'a' + 1;
        dist[u][v] = min(dist[u][v] , w);
    }

    // Floyd
    for(int k = 1 ; k <= 26 ; k++){
        for(int i = 1 ; i <= 26 ; i++){
            for(int j = 1 ; j <= 26 ; j++){
                dist[i][j] = min(dist[i][j] , dist[i][k] + dist[k][j]);
            }
        }
    }

    int ans = 0;
    int len = (int)s.size();
    string res = "";
    for(int i = 0 ; i < len ; i++)
    {
        int u = s[i] - 'a' + 1 , v = t[i] - 'a' + 1;
        
        int min_cost = INF;
        char best_char = ' ';
        
        for(int k = 1 ; k <= 26 ; k++)
        {
            if(dist[u][k] + dist[v][k] < min_cost)
            {
                min_cost = dist[u][k] + dist[v][k];
                best_char = (char)('a' - 1 + k);
            }
        }
        if(min_cost == INF){
            cout << "-1\n";
            return;
        }
        ans += min_cost;
        res.push_back(best_char);
    }
    cout << ans << "\n";
    cout << res << "\n";
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