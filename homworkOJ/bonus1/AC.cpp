#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;
using ll = unsigned long long;

int main(){
	int n, k;
    while(cin >> n >> k){
    	vector<ll> a(n);
        unordered_map<ll, ll> rem[11];
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++){
            for(int j = 1; j <= 10; j++){
                ll r = (a[i] * (ll)pow(10, j))%k;
                rem[j][r]++;
            }
        }
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ll target = (k-(a[i]%k))%k;
            int len = to_string(a[i]).size();
            ans += (rem[len][target]);
            if((a[i] * (ll)pow(10, len))%k == target) ans--;
        }
        cout << ans << "\n";
    }
	return 0;
}