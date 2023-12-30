#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <bitset>
using namespace std;

int n;
vector<bool> visited; 
vector<bitset<26>> v; // v[n][26]

void dfs(int i){
    visited[i] = 1;
    for(int j = 0; j < n; j++){
        if(visited[j] || v[j].none()) continue;
        if((v[i] & v[j])!= bitset<26>(0))	dfs(j);
    }
}

void init(){
    visited.clear();
    v.clear();
}

int main(){
    int t; cin >> t;
    while(t--){
        init();
        cin >> n;
        visited.assign(n, 0);
        v.assign(n, bitset<26>(0));
        for(int i = 0; i < n; ++i){
            string s; cin >> s;
            for(auto c: s){
                v[i].set(c-'a');
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
