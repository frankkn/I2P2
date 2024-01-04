#include <iostream>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

int G[103][103];
vector<int> visited;
map<int, int> mp;
int n;

bool flag = false;

void dfs(int now, int end){
    visited[now] = 1;
    mp[now]++;
    if(now == end){
        flag = true;
        return;
    }
    for(int i = 0; i < n; ++i){
        if(G[now][i] && !visited[i]){
            dfs(i, end);
        }
    }
    visited[now] = 0;
    if(!flag)   mp[now]--;
}

int main(){
    int t; cin >> t;
    while(t--){
        memset(G, 0, sizeof(G));
        cin >> n;
        visited.assign(n+1, 0);
        for(int i = 0; i < n-1; ++i){
            int x, y; cin >> x >> y;
            G[x][y] = 1;
            G[y][x] = 1;
        }
        int q; cin >> q;
        while(q--){
            visited.assign(n+1, 0);
            mp.clear();
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            dfs(x1, x2);
            visited.assign(n+1, 0);
            dfs(y1, y2);
            bool print = false;
            for(auto [x, y]: mp){
                if(y == 2){
                    print = true;
                    cout << "A\n"
                    break;
                }
            }
            if(!print)  cout << "B\n";
        }
    }

    return 0;
}