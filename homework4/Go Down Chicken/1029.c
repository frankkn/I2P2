#include <stdio.h>
#include <stdlib.h>
#define ll long long
#define MOD ((int)1e9+7)

typedef struct _Data
{
    int idx;
    int data;
}Data;
Data a[(int)1e6+3];

ll fp(int x, int y){
	if(y==0)	return 1;
    ll tmp = fp(x, y/2)%MOD;
    if(y%2==1)	return tmp*tmp%MOD*x%MOD;
    else return tmp*tmp%MOD;
}

int cmp(const void *L, const void *R)
{
    Data l = *(Data*)L, r = *(Data*)R;
    // note: we have to confirm that (l.data - r.data) will not cause overflow (larger than 2*10^9 or smaller than -2*10^9)
    if(l.data != r.data) return l.data - r.data; // g[i]小的放前面
    return l.idx - r.idx; // g[i]一樣，前面放idx小的
}

int binary_search(int L, int R, int target){
	while(L < R){
    	int M = (L+R)/2;
        if(a[M].data >= target){
        	R = M;
        }else{
        	L = M+1;
        }
    }
	return R;
}

int main(){
	int n, q; 
    while(scanf("%d%d", &n, &q)!=EOF){
        for(int i = 0; i < n; ++i){
            int tmp;
            scanf("%d(/`A`)/ ~I__I", &tmp);
            a[i].idx = i+1;
            a[i].data = tmp%2==0?fp(2, tmp/2):0; // !!
        }
        qsort(a, n, sizeof(a[0]), cmp);
        while(q--)
        {
            int target;
            scanf("%d", &target);
            int res = binary_search(0, n, target);
            if(res == n || a[res].data != target)
                puts("Go Down Chicken 404");
            else printf("%d\n", a[res].idx);
        }
    }    
	return 0;
}