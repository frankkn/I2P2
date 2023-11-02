#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

int a[(int)1e5+3];
int dp[(int)1e5+3];

int main(){
	int n; scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    dp[0] = 0; dp[1] = abs(a[1]-a[0]);
    for(int i = 2; i < n; ++i){
    	dp[i] = min(dp[i-1] + abs(a[i]-a[i-1]), dp[i-2] + abs(a[i]-a[i-2]));
    }
	printf("%d\n", dp[n-1]);
	return 0;
}