#include <iostream>
using namespace std;
using ll = long long;

int main(){
	int t; cin >> t;
    while(t--){
        ll ans = 0;
    	int A, B, C, D; cin >> A >> B >> C >> D;
        int F[(int)1e6+3] = {0};
    	for(int x = A; x <= B; ++x){
        	F[x + B]++;
            F[x + C + 1]--;
        }
        for(int i = A+B; i <= B+C+1; ++i){
        	F[i] = F[i-1] + F[i];
        }
        for(int i = A+B; i <= B+C; ++i){
        	if(i > C) ans += F[i] * min(i-C, D-C+1);
        
        }
    	cout << ans << endl;
    }

}