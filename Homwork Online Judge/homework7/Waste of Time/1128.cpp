#include <iostream>
#include <vector>
#include <queue> // priority_queue
using namespace std;

const int MAXN = 300000;

vector<vector<int>> G;
vector<int> in_deg;
priority_queue<int, vector<int>, greater<int>> pq;

void solve(){
	int n, m; cin >> n >> m;
    G.assign(n + 1, {});
    in_deg.assign(n, 0);

    while(m--){
    	int u, v; cin >> u >> v;
        G[u].emplace_back(v);
        in_deg[v]++;
    }
    
    for(int i = 0; i < n; ++i){
    	if(in_deg[i] == 0){
        	pq.push(i);
        }
    }
    
    vector<int> ans;
    while(!pq.empty()){
    	int now = pq.top(); pq.pop();
        ans.emplace_back(now);
        for(auto &i: G[now]){
        	in_deg[i]--;
        	if(in_deg[i] == 0){
            	pq.push(i);
            }
        }
    }
    
    for(int i = 0; i < n; ++i){
    	cout << ans[i] << (i == n - 1 ? "\n" : " ");
    }
    
    G.clear();
    in_deg.clear();
    ans.clear();
}

int main(){
	int t; cin >> t;
    while(t--){
    	solve();
    }
	return 0;
}