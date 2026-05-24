#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int , int> PII;

const int N = 1e5 + 10;
int n , m1 , m2;
int p1[N] , p2[N];

int cnt;
PII res[N];

int node1[N] , ptr1;
int node2[N] , ptr2;

int find(int p[] ,int x)
{
    if(p[x] != x) p[x] = find(p , p[x]);
    return p[x];
}

void init()
{
    for(int i = 1 ; i <= n ; i++)
    {
        p1[i] = p2[i] = i;
    }
}

inline bool inTheSameBlock(int x , int y , int p[])
{
    int px = find(p , x) , py = find(p , y);
    return px == py;
}

inline void addEdge(int x , int y)
{
    int px1 = find(p1 , x) , py1 = find(p1 , y);
    int px2 = find(p2 , x) , py2 = find(p2 , y);

    p1[px1] = py1;
    p2[px2] = py2;
}

void solve()
{
    // input
    cin >> n >> m1 >> m2;
    init();

    for(int i = 1 ; i <= m1 ; i++)
    {
        int u , v;
        cin >> u >> v;
        
        int pu = find(p1 , u) , pv = find(p1 , v);
        p1[pu] = pv;
    }

    for(int i = 1 ; i <= m2 ; i++)
    {
        int u , v;
        cin >> u >> v;
        int pu = find(p2 , u) , pv = find(p2 , v);
        p2[pu] = pv;
    }

    // 初步处理
    for(int i = 2 ; i <= n ; i++)
    {
        if(!inTheSameBlock(1 , i , p1) && !inTheSameBlock(1 , i , p2))
        {
            res[++cnt] = {1 , i};
            addEdge(1 , i);
        }
    }

    // 然后处理所有剩下的点
    for(int i = 2 ; i <= n ; i++)
    {
        // 在A中与1相连，但是在B中不与1相连
        if(inTheSameBlock(1 , i , p1) && !inTheSameBlock(1 , i , p2))
        {
            node1[++ptr1] = i;
        }
        // 在B中与1相连，但是在A中不与1相连
        else if(!inTheSameBlock(1 , i , p1) && inTheSameBlock(1 , i , p2))
        {
            node2[++ptr2] = i;
        }
    }

    // 两两配对 
    int i1 = 1 , i2 = 1;
    while(i1 <= ptr1 && i2 <= ptr2)
    {
        int u = node1[i1];
        int v = node2[i2];
        if(!inTheSameBlock(u , v , p1) && !inTheSameBlock(u , v , p2))
        {
            if(u > v) swap(u , v);
            res[++cnt] = {u , v};

            addEdge(u , v);
            i1++;
            i2++;
        }
        else
        {
            if(inTheSameBlock(1 , u , p2)){
                i1++;
            }
            else{
                i2++;
            }
        }
    }

    sort(res + 1 , res + 1 + cnt);
    cout << cnt << "\n";
    for(int i = 1 ; i <= cnt ; i++)
    {
        cout << res[i].first << " " << res[i].second << "\n";
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