#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;
int n, m;
int TBD;

vector<vector<char>> G;
queue<tuple<int,int,int>> Q;
vector<pair<int,int>> dir {{1,0},{-1,0},{0,1},{0,-1}};

int bfs(){
	while(!Q.empty()){
        auto [x,y,z] = Q.front(); Q.pop();
		if(G[y][x] == 'C')	continue;
        else if(G[y][x] == 'T'){
        	TBD--;
            if(TBD == 0){
            	return z;
            }
        }
        G[y][x] = 'C';
        for(auto [dx, dy]: dir){
        	int nx = x+dx, ny = y+dy;
            if(nx < 1 || nx > m || ny < 1 || ny > n || G[ny][nx] == 'C')	continue;
            Q.push(make_tuple(nx, ny, z+1));
        }
    }
    return -1;
}

int main(){
    cin >> n >> m;
    G.assign(n+5, vector<char>(m+5, ' '));
    int sx = 0, sy = 0;
    for(int i = 1; i <= n; ++i){
    	for(int j = 1; j <= m; ++j){
        	cin >> G[i][j];
            if(G[i][j] == 'I'){
            	sx = j;
                sy = i;
            }else if(G[i][j] == 'T'){
            	TBD++;
            }
        }
    }
    Q.push(make_tuple(sx, sy, 0));
    cout << bfs() << endl;    
	return 0;
}