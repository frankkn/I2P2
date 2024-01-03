#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int edges[2000][26];
bool visited[2000];
int n;

void dfs(int i){
	visited[i] = 1;
	for(int j = 0; j < 26; ++j){
    	if(edges[i][j]){
        	for(int k = 0; k < n; ++k){
            	if(!visited[k] && edges[k][j]){
                	dfs(k);
                }
            }
        }
    }
}

void init(){
	memset(edges,0,sizeof(edges));
    memset(visited,0,sizeof(visited));
}

int main(){
    std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
    while(t--){
        init();
    	cin >> n;
        for(int i = 0; i < n; ++i){
        	string s; cin >> s;
            for(auto& c: s){
            	edges[i][c-'a'] = 1;
            }
        }
        int g = 0;
        for(int i = 0; i < n; ++i){
        	if(!visited[i]){
            	g++;
                dfs(i);
            }
        }
        cout << g << '\n';
    }
    return 0;
}