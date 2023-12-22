#include <stdio.h>

int a[(int)2e6+3];

int bs(int L, int R, int target){
	while(L < R){
    	int M = (L+R)/2;
        if(a[M] >= target){
        	R = M;
        }else{
        	L = M+1;
        }
    }
	return R;
}

int main(){
	int n,q; 
    while(scanf("%d%d", &n, &q) != EOF){
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        while(q--){
            int target; scanf("%d", &target);
            int res = bs(0, n, target);
            if(res == n || a[res] != target){
                printf("Break your bridge!\n");
            }else{
                printf("%d\n", res+1);
            }
        }
    }
	return 0;
}