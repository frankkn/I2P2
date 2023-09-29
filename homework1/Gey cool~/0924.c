#include <stdio.h>
#define ll long long
#define MAXN ((int)2e6+1)

int arr[MAXN];
ll pre[MAXN];

int main(){
	int n, q;
    while(scanf("%d%d", &n, &q) != EOF){
    	for(int i = 1; i <= n; i++){
        	scanf("%d", &arr[i]);
            pre[i] = pre[i-1]+arr[i];
        }
        int a, b, maxa, maxb;
        ll maxv = -1;
        while(q--){
            scanf("%d%d", &a, &b);
            if(a <= b){
            	ll cur = pre[b] - pre[a-1];
                if(cur > maxv){
                 	maxa = a;
                    maxb = b;
                    maxv = cur;
                }
            }else{
            	ll cur = pre[n]-pre[a-1]+pre[b];
                if(cur > maxv){
                 	maxa = a;
                    maxb = b;
                    maxv = cur;
                }
            }	
        }
        printf("Max_range: (%d,%d); Value: %lld\n", maxa, maxb, maxv);
    }
}