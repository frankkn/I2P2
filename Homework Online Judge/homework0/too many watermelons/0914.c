#include <stdio.h>

int pos[(int)1e6];

int main(){
	int n; scanf("%d", &n);
    for(int i = 1; i <= n; ++i){
        int num;
    	scanf("%d", &num);
        pos[num] = i;
    }
    int now = 0;
    for(int i = 1; i <= n; ++i){
        int cur;
        scanf("%d", &cur);
        if(pos[cur] > now){
        	printf("%d", pos[cur]-now);
            now = pos[cur];
        }else{
        	printf("0");
        }
        if(i == n) printf("\n");
        else printf(" ");
    }
	return 0;
}