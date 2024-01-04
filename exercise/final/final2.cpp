#include <iostream>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

int G[103][103];
vector<int> visited;
int n;
int prev[103];

void dfs(int now){
    visited[now] = 1;
    for(int i = 0; i < n; ++i)
        if(G[now][i] && !visited[i])
            dfs(i), prev[i] = now;
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
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            vector<int> p1, p2;
            memset(prev, 0, sizeof(prev));
            visited.assign(n+1, 0);
            dfs(x1);
            int start = prev[x1] = -1;
            int end = x2;
            while(start != end){
                p1.push_back(end);
                end = prev[end];
            }

            memset(prev, 0, sizeof(prev));
            visited.assign(n+1, 0);
            dfs(y1);
            start = prev[y1] = -1;
            end = y2;
            while(start != end){
                p2.push_back(end);
                end = prev[end];
            }
            
            for(auto x:p1){
                for(auto y:p2){
                    if(x==y){
                        cout << "A\n";
                        goto end;
                    }
                }
            }
            cout << "B\n";
            end:;
        }   
    }

    return 0;
}