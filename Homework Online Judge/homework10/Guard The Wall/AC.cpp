#include <bits/stdc++.h>
using namespace std;

int wall[5003], L[5003], R[5003], pre[5003];

void init(){
	memset(wall, 0, sizeof(wall));
    memset(pre, 0, sizeof(pre));
}

int main(){
	int t; cin >> t;
    while(t--){
    	init();
        int n, q; cin >> n >> q;
        // 1. build wall
        for(int i = 1; i <= q; ++i){
        	cin >> L[i] >> R[i];
            for(int j = L[i]; j <= R[i]; ++j){
            	wall[j]++;
            }
        }
        
        int wall_guard = 0;
        // 2. calculate wall guard
        for(int i = 1; i <= n; ++i){
        	if(wall[i]) wall_guard++;
        }
        
        int ans = 0, tmp = wall_guard;
        // 3. remove L[i]~R[i]
        for(int i = 1; i <= q; ++i){
        	int min_loss = n;
            // 3.1 remove L[i]~R[i]
            for(int j = L[i]; j <= R[i]; ++j){
            	wall[j]--;
                if(wall[j] == 0) wall_guard--;
            }
            
            // 3.2 build pre[1~n]
            for(int j = 1; j <= n; ++j){
            	if(wall[j] == 1) pre[j] = pre[j-1]+1;
            	else pre[j] = pre[j-1];
            }
            
            // 3.3 find min loss
            for(int j = i+1; j <= q; ++j){
            	int loss = pre[R[j]] - pre[L[j]-1];
            	min_loss = loss < min_loss ? loss:min_loss;
            }
            
            // 3.4 ans
            ans = (wall_guard-min_loss) > ans ? (wall_guard-min_loss): ans;
            
            // 3.5 recover L[i]~R[i]
            for(int j = L[i]; j <= R[i]; ++j){
                wall[j]++;
            }        
        
            // 3.6 recover wall_guard
            wall_guard = tmp;
        }
        cout << ans << endl;
    }
	return 0;
}