#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void solve(){
	int n, m; cin >> n >> m;
    vector<vector<int>> G;
    G.assign(n+1, {});
    vector<int> in_deg(n+1, 0);
    priority_queue<int, vector<int>, greater<int>> q;
    while(m--){
    	int u, v; cin >> u >> v;
        G[u].emplace_back(v);
        in_deg[v]++;
    }
    for(int i = 0; i < n; ++i){
    	if(in_deg[i] == 0) q.push(i);
    }
    vector<int> ans;
    while(!q.empty()){
    	auto u = q.top(); q.pop();
    	ans.emplace_back(u);
        for(auto v: G[u]){
        	if(--in_deg[v] == 0) q.push(v);
        }
    }
    auto last = ans.end(); last--;
    for(auto it = ans.begin(); it != ans.end(); it++){
    	cout << *it << (it == last ? "\n": " ");
    }
}

int main(){
	int t; cin >> t;
    while(t--){
    	solve();
    }

	return 0;
}