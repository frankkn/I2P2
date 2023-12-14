#include <stdio.h>
#include <string.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int main(){
  int t; scanf("%d", &t);
  while(t--){
    int n, q; scanf("%d %d", &n, &q);
    int L[5003] = {0}, R[5003] = {0}, W[5003] = {0};
    int _max = 0;
    for(int i = 0; i < q; ++i){
      scanf("%d %d", &L[i], &R[i]);
      for(int j = L[i]; j <= R[i]; ++j){
        if(W[j] == 0) _max++; // longest wall that guarded
        W[j]++;
      }
    }

    int ans = 0;
    for(int i = 0; i < q; ++i){
      for(int j = i+1; j < q; ++j){
        int cur = _max;
        // Case1: No overlap
        if(R[i] < L[j] || R[j] < L[i]){
          for(int k = L[i]; k <= R[i]; ++k){
            if(cur <= ans) break;
            if(W[k]-1 == 0) cur--;
          }
          for(int k = L[j]; k <= R[j]; ++k){
            if(cur <= ans) break;
            if(W[k]-1 == 0) cur--;
          }
        }else{
        // Case2: Overlap
          int Lmost = min(L[i], L[j]);//1
          int second = max(L[i], L[j]);//2 
          int third = min(R[i], R[j]);//3
          int Rmost = max(R[i], R[j]);//4
          for(int k = Lmost; k <= Rmost; ++k){
            if(cur <= ans) break;
            if(k >= second && k <= third && W[k] - 2 == 0) cur--;
            if(k < second && W[k] -1 ==0) cur--;
            if(k > third && W[k] -1 == 0) cur--;
          }
        }
        ans = max(ans, cur);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}