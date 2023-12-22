#include <stdio.h>

int a[(int)2e6+3];

int bs(int L, int R, int target){
    while(L <= R){
		int M = (L+R)/2;
	    if(a[M] > target){
        	R = M-1;
        }else if(a[M] < target){
        	L = M+1;
        }else{
        	return M;
        }
    }
	return -1;
}

int main(){
	int n, q; 
    while(scanf("%d%d", &n, &q) != EOF){
        for(int i = 0; i < n; ++i)	scanf("%d", &a[i]);
        while(q--){
            int target; scanf("%d", &target);
            int idx = bs(0, n-1, target);
            if(idx == -1)	printf("Break your bridge!\n");
            else printf("%d\n", idx+1);
        }
    }
	return 0;
}