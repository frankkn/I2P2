#include <cstdio>
#include <cstring>
const int MAX_N=1e4+4;

int t, n, r, k;
int x[MAX_N], y[MAX_N];
bool visited[MAX_N];

int dist2(int i, int j)
{ return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]); }
int dfs(int now)
{
	visited[now] = true;
	int res = 1;
	for(int i=0; i<n; i++)
		if(!visited[i] && dist2(now,i)<=r*r)
			res += dfs(i);
	return res;
}

int main()
{
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &r, &k);
        int lt_k=0, geq_k=0;
        memset(visited, false, sizeof(visited));
        for(int i=0; i<n; i++) scanf("%d%d", &x[i], &y[i]);
        for(int i=0; i<n; i++)
            if(!visited[i])
            {
                int cnt = dfs(i);
                if(cnt<k) lt_k++;
                else geq_k++;
            }
        printf("%d %d\n", lt_k, geq_k);
    }
	return 0;
}