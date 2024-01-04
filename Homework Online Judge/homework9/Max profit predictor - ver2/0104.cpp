#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main(){
	int t; cin >> t;
    while(t--){
    	int d; cin >> d;
        vector<int> p(d+1, 0);
        ll ans = 0;
        for(int i = 1; i <= d; ++i){
            cin >> p[i];
            if(p[i] > p[i-1]) ans += (p[i]-p[i-1]);
        }
        ans -= p[1];
        cout << ans << endl;
    }
	return 0;
}