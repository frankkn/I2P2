#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

/*
d: 6 
stock price: 7 1 2 5 6 4
so we can get max profix by buy on day 2 and sell on day 5, thus we get 6 - 1 = 5.
return max profit which is $5
*/

int a[(int)1e6+3];
int b[(int)1e6+3];

int main(){
    int d;
    scanf("%d", &d); // 6
    for(int i = 0; i < d; ++i){ // 7 1 2 5 6 4
        scanf("%d", &a[i]);
    }
    int _min = 999999;
    for(int i = 0; i < d; ++i){
        if(_min > a[i]) _min = a[i];
        b[i] = min(_min, a[i]); // b[i]:從a[0]~a[i]中，當前最小的值
    }

    int _max = 0;
    for(int i = 1; i < d; ++i){
        if(a[i] - b[i-1] > _max)  _max = a[i] - b[i-1];
    }

    printf("%d\n", _max);

    return 0;
}