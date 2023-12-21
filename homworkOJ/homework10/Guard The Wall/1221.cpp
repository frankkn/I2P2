#include <iostream>
#include <cstring>
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
        
        // build wall
        for(int i = 1; i <= q; ++i){
        	cin >> L[i] >> R[i];
            for(int j = L[i]; j <= R[i]; ++j){
            	wall[j]++;
            }
        }
        
        // calculate wall guarded
        int wall_guard = 0;
        for(int i = 1; i <= n; ++i){
        	if(wall[i]){
            	wall_guard++;
            }
        }
        
        int ans = 0, tmp = wall_guard;
        for(int i = 1; i <= q; ++i){
        	int min_loss = n;
            
            // earase L[i]~R[i]
            for(int j = L[i]; j <= R[i]; ++j){
            	wall[j]--;
                if(wall[j]==0)	wall_guard--;
            }
            
            // build pre[1~n] (wall[k] <= 1)
            for(int j = 1; j <= n; ++j){
            	if(wall[j] == 1)	pre[j] = pre[j-1]+1;
                else pre[j] = pre[j-1];
            }
            
            // find min lost
            for(int j = i+1; j <= q; ++j){
            	int loss = pre[R[j]] - pre[L[j]-1];
            	min_loss = loss < min_loss? loss: min_loss;
            }
            
            // calculate ans
            if(ans < wall_guard-min_loss) ans = wall_guard-min_loss;
            
            // recover L[i]~R[i]
            for(int j = L[i]; j <= R[i]; ++j){
            	wall[j]++;
            }
            
            // recover wall guard
            wall_guard = tmp;
        }
    	cout << ans << endl;
    }
	return 0;
}
