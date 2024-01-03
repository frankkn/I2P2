#include <iostream>
using namespace std;

const int MAXN = 301, MAXK = 301;
const long long INF = 1ll<<62;
int n, k;
int a[MAXN]; // starts from 1
long long pre[MAXN];
long long dp[MAXN][MAXK];

int main(){
	int t; cin >> t;
    while(t--){
    	cin >> n >> k;
        for(int i = 1; i <= n; ++i){
            cin >> a[i];
    		pre[i] = pre[i-1] + a[i];
        }
        // dp initialization
        for(int i = 1; i <= n; ++i){
        	dp[i][1] = pre[i];
        }
        // iterate dp[i][j]:前i個數字分成j組的最小最大值
        for(int i = 2; i <= n; ++i){
        	for(int j = 2; j <= min(i,k); ++j){
                dp[i][j] = INF;
           		// dp[alpha][j-1] , sum(alpha+1, i)
                // dp[alpha][j-1] , (pre[i] - pre[alpha+1-1])
                
                for(int alpha = j-1; alpha < i; ++alpha){
                	dp[i][j]=min(max(dp[alpha][j-1], (pre[i]-pre[alpha])), dp[i][j]);
                }
            }
        }
        cout << dp[n][k] << endl;
    }
	return 0;
}