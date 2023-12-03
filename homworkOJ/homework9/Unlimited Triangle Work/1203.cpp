#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main(){
	int t; cin >> t;
    while(t--){
    	int A, B, C, D; cin >> A >> B >> C >> D;
        vector<int> F;
        F.assign(100000 ,0);
        for(int x = A; x <= B; ++x){
        	F[x+B]++;
            F[x+C+1]--;
        } 
        for(int i = A+B; i <= B+C+1; ++i){
        	F[i] += F[i-1];
        }
        ll ans = 0;
        for(int i = A+B; i <= B+C; ++i){
            if (i > C) {
                ans += F[i] * min(i-C, D-C+1); // F[i] * z有幾種可能
            }
        }
    	cout << ans << endl;
    }
	return 0;
}