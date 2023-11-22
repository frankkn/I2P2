#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100000;

int dp[MAXN+1][3];

int main()
{
    // I/O boost
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    for(int i = 1; i <= n; ++i){
        int a, b, c; cin >> a >> b >> c;
        dp[i][0] = max(dp[i-1][1], dp[i-1][2]) + a;
        dp[i][1] = max(dp[i-1][0], dp[i-1][2]) + b;
        dp[i][2] = max(dp[i-1][0], dp[i-1][1]) + c;
    }

    cout << max({dp[n][0], dp[n][1], dp[n][2]}) << '\n';
    return 0;
}