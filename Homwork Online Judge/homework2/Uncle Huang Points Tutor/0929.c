#include <stdio.h>
#define ll long long

ll fast_pow(ll x, ll y, ll m){
    if(y == 0)	return 1%m;
	ll tmp = fast_pow(x, y/2, m)%m;
	if(y%2==1) return tmp*tmp%m*x%m;
    else return tmp*tmp%m;
}

int main(){
	ll x, y, m;
    scanf("%lld%lld%lld", &x, &y, &m);
    printf("%lld\n", fast_pow(x%m, y, m));
	return 0;
}