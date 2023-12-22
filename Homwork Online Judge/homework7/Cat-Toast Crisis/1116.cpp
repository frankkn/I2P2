#include <iostream>
using namespace std;
const int MAX_N = 1e4;
bool visited[MAX_N];
int x[MAX_N], y[MAX_N]; // point i: (x[i], y[i])

int dist2(int i, int now){
    return (x[i]-now[i])*(x[i]-now[i]) + (y[i]-now[i])*(y[i]-now[i]);
}

int cnt;
void dfs(int now){
    visited[now] = true;
    for(int i = 0; i < n; ++i){
        if(!visited[i] && dist2(i, now) <= r*r)
            dfs(i);
            cnt++;
        }
    }
}

/*
int dfs(int now){
    int res = 1;
    visited[now] = true;
    for(int i = 0; i < n; ++i){
        if(!visited[i] && dist2(i, now) <= r*r)
            res += dfs(i);
        }
    }
    return res;
}
*/

int main(){

    for(int i = 0; i < n; ++i){
        if(!visited[i]){
            dfs(i);
        }
    }

    return 0;
}