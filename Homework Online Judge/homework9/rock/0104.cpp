#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> G;

int main(){
	int t; cin >> t;
    while(t--){
    	int m, n; cin >> m >> n;
        G.assign(m+1, vector<int>(n+1, {}));
        for(int i = 1; i <= m; ++i){
        	for(int j = 1; j <= n; ++j){
            	cin >> G[i][j];
            }
        }
        for(int i = 1; i <= m; ++i){
        	for(int j = 1; j <= n; ++j){
            	G[i][j] += G[i-1][j] + G[i][j-1] - G[i-1][j-1];
            }
        }
        int q; cin >> q;
        while(q--){
        	int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
            cout << G[x2][y2]-G[x1-1][y2]-G[x2][y1-1]+G[x1-1][y1-1] << endl;
        }
    }
	return 0;
}