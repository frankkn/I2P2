#include <stdio.h>
#define ll long long

ll a[(int)1e6+3];
ll pre[(int)1e6+3];

int main(){
	int n, q; scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; ++i){
    	scanf("%lld", &a[i]);
        if(a[i] > 0)	pre[i] = pre[i-1]+a[i];
        else pre[i] = pre[i-1];
    }
    while(q--){
    	int L, R, M;
        scanf("%d%d%d", &L, &R, &M);
        printf("%lld\n", pre[L+M-1] - pre[L-1]);
    }
	return 0;
}