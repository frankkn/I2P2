#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n; cin >> n;
    vector<vector<int>> dp(n+1,vector<int>(3,0));
    for(int i = 1; i <= n; ++i){
        int a,b,c; cin >> a >> b >> c;
    	dp[i][0] = max(dp[i-1][1]+a, dp[i-1][2]+a);
        dp[i][1] = max(dp[i-1][0]+b, dp[i-1][2]+b);
        dp[i][2] = max(dp[i-1][0]+c, dp[i-1][1]+c);
    }
	cout << max({dp[n][0], dp[n][1], dp[n][2]}) << "\n";
	return 0;
}