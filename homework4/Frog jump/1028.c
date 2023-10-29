#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

int a[(int)1e5+3];
int dp[(int)1e5+3];

int main(){
	int n; scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    dp[1]= 0; dp[2] = abs(a[2]-a[1]);
    for(int i = 3; i <= n; ++i){
    	dp[i] = min(dp[i-1] + abs(a[i]-a[i-1]) , dp[i-2]+ abs(a[i]-a[i-2]));
    }
	printf("%d\n", dp[n]);
	return 0;
}