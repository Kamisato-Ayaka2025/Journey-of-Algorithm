#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;

int n , m;
int a[N];

LL sum;



class Point{
public:
    int weight , idx;
    Point(int w , int id) : weight(w) , idx(id) {};

    bool operator < (const Point &W) const{
        return weight < W.weight;
    }
};

vector<Point> vec;
int p[N] , sz[N];
void init()
{
    vec.clear();
    sum = 0ll;
    for(int i = 1 ; i <= n ; i++)
    {
        p[i] = i;
        sz[i] = 1;
    }
}

int find(int x)
{
    while(p[x] != x) x = p[x];
    return p[x];
}

bool unite(int u , int v)
{
    u = find(u) , v = find(v);
    if(sz[u] > sz[v]) swap(u , v);
    if(u != v)
    {
        p[v] = u;
        sz[u] += sz[v];
        return true;
    }
    return false;
}

void solve()
{
    cin >> n >> m;
    init();
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
        vec.emplace_back(a[i] , i);
    }

    sort(vec.begin() , vec.end());

    for(auto v : vec)
    {
        int pos = v.idx , w = v.weight;

        if(w >= m) break;

        for(int i = pos - 1 ; i >= 1 ; i--)
        {
            if(a[i] % w == 0){
                if(unite(i , pos)){
                    sum += w;
                }
            }
            else break;
        }

        for(int i = pos + 1 ; i <= n ; i++)
        {
            if(a[i] % w == 0){
                if(unite(i , pos)){
                    sum += w;
                }
            }
            else break;
        }
    }

    for(int i = 1 ; i < n ; i++)
    {
        if(unite(i , i + 1)){
            sum += m;
        }
    }

    cout << sum << "\n";
    return;
}

#define _DEBUG
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
    while(T--)solve();
    return 0;
}