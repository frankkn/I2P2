#include <stdio.h>
#define MAXN ((int)1e6+3)
#define ll long long

int a[MAXN];
ll pre[MAXN];

int count_one(int i){
	int cnt = 0;
    while(i > 0){
    	if (i % 10 == 1) cnt++;
        i /= 10;
    }
	return cnt;
}

int main(){
	for(int i = 1; i < MAXN; ++i){
    	a[i] = count_one(i);
        pre[i] = pre[i-1] + a[i];
    }
    
    int t; scanf("%d", &t);
    while(t--){
    	int a,b; scanf("%d%d", &a, &b);
        printf("%lld\n", pre[b]-pre[a-1]);
    }
	return 0;
}