#include <stdio.h>
#include <stdlib.h>
#define ll long long 
#define MOD ((int)1e9+7)

typedef struct _Matrix{
	ll d[2][2];
}Matrix;

Matrix matmul(Matrix L, Matrix R){
	Matrix A; memset(A.d, 0, sizeof(A.d));
    for(int i = 0; i < 2; ++i) for(int j = 0; j < 2; ++j) for(int k = 0; k < 2; ++k){
    	(A.d[i][j] += (L.d[i][k] * R.d[k][j] %MOD) ) %MOD;
    }
	return A;
}

Matrix Identity(){
	Matrix m; memset(m.d, 0, sizeof(m.d));
    ll values[2][2] = {{1,0},{0,1}};
    for(int i = 0; i < 2; ++i) for(int j = 0; j < 2; ++j){
    	m.d[i][j] = values[i][j];
    }
    return m;
}

Matrix init_x(Matrix x){
	ll values[2][2] = {{1,1},{1,0}};
    for(int i = 0; i < 2; ++i) for(int j = 0; j < 2; ++j){
    	x.d[i][j] = values[i][j];
    }
    return x;
}


Matrix init_p(Matrix p){
	ll values[2][2] = {{1,0},{1,0}};
    for(int i = 0; i < 2; ++i) for(int j = 0; j < 2; ++j){
    	p.d[i][j] = values[i][j];
    }
    return p;
}

Matrix fp(Matrix x, ll i){
	if(i == 0) return Identity();
    Matrix tmp = fp(x, i/2);
    if(i%2 == 1)	return matmul(matmul(tmp, tmp), x);
    else	return matmul(tmp, tmp);

}

int F(ll i){
	if(i == 1 || i == 2) return 1;
    else{
    	Matrix x, p, res;
        x = init_x(x);
        p = init_p(p);
        res = matmul(fp(x, i-2), p);
    	return res.d[0][0] % MOD;
    }

}

int main(){
	ll i; 
    while( scanf("%lld", &i) != EOF ){
    	int ans = F(i);
        printf("%d\n", ans);
    }
	return 0;
}