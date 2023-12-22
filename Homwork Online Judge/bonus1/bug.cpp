#include <iostream>
#include <vector>
#include <map>
#include <cmath> // pow
#include <algorithm> // sort & lower_bound & upper_bound
#include <string> // to_string
using namespace std;
using ll = long long;

int main(){
	int n, k; 
    while( cin >> n >> k ){
    	vector<ll> a(n,0);
        for(int i = 0; i < n; ++i){
            cin >> a[i];
        }
        
        map<int, vector<int>> rem;
        for(int i = 1; i <= 9; ++i){
            for(int j = 0; j < n; ++j){
        		ll tmp = a[j] * (ll)pow(10, i) % k;
                rem[i].emplace_back(tmp);
            }
            sort(rem[i].begin(), rem[i].end());
        }
        
        int ans = 0;
        for(auto& a_i: a){
        	int len = to_string(a_i).size();
            int target = k - (a_i % k); 
            // Case1: a_i 不是k的倍數
            if(target != k){
            	ans += upper_bound(rem[len].begin(), rem[len].end(), target) - lower_bound(rem[len].begin(), rem[len].end(), target);
                // 檢查有沒有用到自己
                if((a_i * (ll)pow(10, len) + a_i ) % k == 0) ans--;
            // Case2: a_i 是k的倍數
            }else{
				ans += upper_bound(rem[len].begin(), rem[len].end(), 0) - lower_bound(rem[len].begin(), rem[len].end(), 0);
                if((a_i * (ll)pow(10, len) + a_i ) % k == 0) ans--;
            }
        }
        cout << ans << endl;
    }
    
}