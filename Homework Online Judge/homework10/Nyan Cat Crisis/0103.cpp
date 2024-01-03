#include <iostream>
#include <cstring>
using namespace std;

int x[501], y[501];
int visited[501];
int n, r, k; 

int dist2(int i,int j){
	return (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
}

int dfs(int i){
	visited[i] = 1;
    int cnt = 1;
    for(int j = 0; j < n; ++j){
    	if(!visited[j] && dist2(i,j)<= r*r){
        	cnt += dfs(j);
        }
    }
    return cnt;
}

void init(){
	memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    memset(visited,0,sizeof(visited));
}
        
int main(){
	int t; cin >> t;
    while(t--){
        init();
    	cin >> n >> r >> k;
        for(int i = 0; i < n; ++i){
        	cin >> x[i] >> y[i];
        }
    	int g1 = 0, g2 = 0;
        for(int i = 0; i < n; ++i){
        	if(!visited[i]){
            	int tmp = dfs(i);
                if(tmp < k)	g1++;
                else g2++;
            }
        }
        cout << g1 << " " << g2 << '\n';
    }
	return 0;
}