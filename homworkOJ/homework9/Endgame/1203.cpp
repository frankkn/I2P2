#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

int n, m;
vector<vector<char>> G;
queue<tuple<int,int,int>> q;
int TBD = 0;
vector<pair<int,int>> dir{{0,-1},{0,1},{-1,0},{1,0}};

int bfs(){
	while(!q.empty()){
    	auto [x,y,dist] = q.front(); q.pop(); // 不可以用auto& 原因是q.front() return rvalue
        if(G[y][x] == 'C')	continue;
        if(G[y][x] == 'T'){
        	if(--TBD == 0)	return dist;
        }
        G[y][x] = 'C'; // Mark成'C'，反正也不會再走
    	for(auto&[dx,dy]: dir){ // 朝四個方向走
        	int nx = x+dx, ny = y+dy;
            if(nx <= 0 || nx > m || ny <= 0 || ny > n)	continue;
            if(G[ny][nx] == 'C')	continue;
            q.push(make_tuple(nx, ny, dist+1));
        }
    }
	return -1;
}

int main(){
	cin >> n >> m;
	G.assign(n+2, vector<char>(m+2, ' '));
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j){
    	cin >> G[i][j];
        if(G[i][j] == 'I')	q.push(make_tuple(j, i, 0));
        else if(G[i][j] == 'T')	TBD++;    
    }
	cout << bfs();
    return 0;
}