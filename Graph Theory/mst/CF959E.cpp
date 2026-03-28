#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll n;
    cin >> n;

    ll total_weight = 0;
    ll weight = 1;
    while (weight < n) {
        ll edges = n / (weight * 2);

        if (n % (weight * 2) > weight) {
            edges++;
        }

        total_weight += edges * weight;
        weight *= 2;
    }
    cout << total_weight << endl;

    return 0;
}