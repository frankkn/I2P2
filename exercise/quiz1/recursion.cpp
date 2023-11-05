#include <stdio.h>

int k, n; // k <= 12, n <= 22

int to_print[30];
int used[30];

void dfs(int idx, int num){
    if(idx == k){
        for(int i = 0; i < k; ++i){
            printf("%d", to_print[i]);
            if(i == (k-1)) printf("\n");
            else printf(" ");
        }
        return;
    }
    for(int i = num; i <= n; ++i){
        if(idx > 0 && i < to_print[i-1])    continue;
        if(!used[i]){
            used[i] = 1;
            to_print[idx] = i;
            dfs(idx+1, i+1);
            to_print[idx] = 0;
            used[i] = 0;
        }
    }
}

int main(){
    scanf("%d%d", &k, &n);
    dfs(0, 1);
    return 0;
}