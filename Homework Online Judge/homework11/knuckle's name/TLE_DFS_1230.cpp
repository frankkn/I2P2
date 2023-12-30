#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int edges[2001][26];
int visited[2001];

int n;
void dfs(int i){
	visited[i] = 1;
    for(int j = 0; j < n; ++j){
    	if(visited[j]) continue;
		for(int k = 0; k < 26; ++k){
            if(edges[i][k] && edges[j][k]){
            	dfs(j);
                break;
            }
        }
    }
}

void init(){
	memset(edges, 0, sizeof(edges));
	memset(visited, 0, sizeof(visited));
}

int main(){
	int t; cin >> t;
    while(t--){
        init();
    	cin >> n;
        for(int i = 0; i < n; ++i){
        	string s; cin >> s;
            for(auto c: s){
            	edges[i][c-'a'] = 1;
            }
        }
        int g = 0; // group
        for(int i = 0; i < n; ++i){
        	if(!visited[i]){
            	g++;
                dfs(i);
            }
        }
        cout << g << endl;
    }
	return 0;
}