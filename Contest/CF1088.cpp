#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    for (int i = 0; i < n; ++i) {
        if (n == 1) { // 长度为1或者2
            cout << 1 << (i == n - 1 ? "" : " ");
            continue;
        }

        bool can_be_one = false;

        for (int start = max(0, i - 2); start <= i && start + 2 < n; ++start) {
            int a = p[start];
            int b = p[start + 1];
            int c = p[start + 2];

            int max_val = max({a, b, c});
            int min_val = min({a, b, c});
            
            if (p[i] != max_val && p[i] != min_val) {
                can_be_one = true;
                break;
            }
        }

        if (can_be_one) {
            cout << 1;
        } else {
            cout << 2;
        }
        
        cout << (i == n - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}