#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Point{
	int x, y;
};
vector<Point> p;

int n, r, k;
vector<bool> visited(n, false);

int dist2(int i, int j){
	return (p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y);
}

int dfs(int i){
	visited[i] = true;
    int res = 1;
    for(int j = 0; j < n; ++j){
    	if(!visited[j] && dist2(i,j) <= r*r){
        	res += dfs(j);
        }
    }
	return res;
}

int main(){
	int t; cin >> t;
    while(t--){
    	cin >> n >> r >> k;
        p.assign(n, {});
        visited.assign(n, false);
        for(int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;
        int ge = 0, less = 0;
        for(int i = 0; i < n; ++i){
        	if(!visited[i]){
            	int cnt = dfs(i);
                if(cnt >= k) ge++;
                else less++;
            }
        }
        cout << less << " " << ge << endl;
    }
    return 0;
}