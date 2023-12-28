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

        // 條件1: C <= z <= D
        // 條件2: z < i implies z <= i-1
        // 總和條件1&2成立的z: min(D, i-1) - C +1
        
        for(int i = A+B; i <= B+C; ++i){
        	ll num_of_z = min(D, i-1) - C +1;
            if(num_of_z < 0) continue;
            ans += F[i] * num_of_z;
        
        }
    	cout << ans << endl;
    }

}