#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using ll = long long;
using namespace std;
const int MAX_N = 300000;

int n, m;
vector<int> G[MAX_N];
int in_deg[MAX_N];
// The priority_queue declared here has complex template definition.
// You can replace "greater<int>" with "less<int>" to pop largest number to the top of the priority_queue.
priority_queue<int, vector<int>, greater<int>> pq;

void solve()
{
	cin >> n >> m;
	for(int i=0, u, v; i<m; ++i)
	{
		cin >> u >> v;
		// connection: u -> v: query G[u], should be able to find "v" in the list.
		// out-degree of u: just query G[u].size().
		G[u].emplace_back(v);
		in_deg[v]++;
	}

	// find source nodes (nodes with 0 in-degree)
	for(int i=0; i<n; ++i)
		if(in_deg[i] == 0)
			pq.push(i);

	vector<int> ans;
	ans.reserve(n);
	while(!pq.empty())
	{
        // Get the smallest number from the nodes with 0 in-degree by priority_queue.
		int now = pq.top(); pq.pop();
        // Put into the order (ans).
		ans.emplace_back(now);
        // Iterate over all elements in G[now]: the "i" here is equal to G[now][x] in "for(int x=0; x<G[now].size(); ++x);".
		for(int &i : G[now])
		{
            // Since now -> i is an edge, we remove the node "now" should also remove all the edges start from now, which means reduce the in-degree of node i.
			in_deg[i]--;
            // If after the edge removal, the in-degree reduce to 0, the node i can be a candidate.
			if(in_deg[i] == 0)
				pq.push(i);
		}
	}
	for(int i=0; i<n; ++i)
		cout << ans[i] << ((i != n-1) ? " " : "\n");

	// Remember to reset all edges and in-degrees. Although after the processes above, these stuff should have been cleared.
	for(int i=0; i<n; ++i) G[i].clear();
	memset(in_deg, 0, sizeof(int)*n);
}

int main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}