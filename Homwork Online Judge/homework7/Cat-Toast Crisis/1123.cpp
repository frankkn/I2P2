#include <iostream>
using namespace std;

int n,r;
bool visited[1003];

struct Point{
	int x, y;
};

Point points[1003];

int dist2(int now, int i){
	return (points[now].x-points[i].x)*(points[now].x-points[i].x) + (points[now].y-points[i].y)*(points[now].y-points[i].y);
}

int dfs(int now){
	visited[now] = 1;
    int res = 1;
    for(int i = 0; i < n; ++i){
    	if(!visited[i] && dist2(now, i) <= r*r){
        	res += dfs(i);
        }
    }
    return res;
}


int main(){
	cin >> n >> r;
    for(int i = 0; i < n; ++i){
    	cin >> points[i].x >> points[i].y;
    }
    int g1 = 0, g2 = 0;
    for(int i = 0; i < n; ++i){
    	int res = 0;
        if(!visited[i]){
        	res = dfs(i);
            if(res == 1)	g1++;
			else	g2++;
        }
    }
    cout << g1 << " " << g2 << "\n";
    return 0;
}