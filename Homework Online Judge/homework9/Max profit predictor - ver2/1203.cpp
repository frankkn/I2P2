#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main(){
	int t; cin >> t;
    while(t--){
    	int d; cin >> d;
        vector<int> a;	a.assign(d, 0);
        ll ans = 0;
        for(int i = 0; i < d; ++i){
            cin >> a[i];
        	if(i > 0 && a[i] > a[i-1]){
            	ans += (a[i]-a[i-1]);
            }
        }
        cout << ans << endl;
    }

	return 0;
}