#include <iostream>
#include <vector>
using namespace std;

int main(){
	int t; cin >> t;
    while(t--){
    	int m, n; cin >> m >> n;
        vector<vector<int>> dp;
        dp.assign(m+2,vector<int>(n+2,0)); // 要開+2
        for(int i = 1; i <= m; ++i) for(int j = 1; j <= n; ++j){
        	cin >> dp[i][j];
            dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
        }
    	int q; cin >> q;
        while(q--){
        	int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            cout << dp[x2][y2] - dp[x1-1][y2] - dp[x2][y1-1] + dp[x1-1][y1-1] << endl;        
        }
    }
	return 0;
}