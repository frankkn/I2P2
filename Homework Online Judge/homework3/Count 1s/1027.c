#include <stdio.h>
#define ll long long
#define MAXN ((int)1e6+1)

ll pre[MAXN];

int find_one(int i){
	int ans = 0;
    while(i > 0){
    	ans += (i%10==1?1:0);
    	i /= 10;
    }
    return ans;
}

int main(){
	int t; scanf("%d", &t);
    for(int i = 1; i <= MAXN; i++){
    	pre[i] = pre[i-1]+ find_one(i);	
    }
    while(t--){
    	int a, b; scanf("%d%d", &a, &b);
        printf("%lld\n", pre[b] - pre[a-1]);
    }
	return 0;
}