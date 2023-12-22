#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100000;
int a[MAXN+1];

int main()
{
    // I/O boost
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    sort(a, a+n);

    int q; cin >> q;
    while(q--){
        int x;  cin >> x;
        cout << upper_bound(a, a+n, x) - lower_bound(a, a+n, x) << '\n';
    }

    return 0;
}