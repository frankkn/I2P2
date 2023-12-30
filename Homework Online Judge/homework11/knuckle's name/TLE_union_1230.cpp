#include <iostream>
#include <string>
#include <cstring>
#include <set>
using namespace std;

int edges[2001][26];
int parent[2001];
int n;

void init() {
    memset(edges, 0, sizeof(edges));
    memset(parent, 0, sizeof(parent));
}

int find_root(int x) {
    if (x == parent[x]) return x;
    int root = find_root(parent[x]);
    return parent[x] = root;
}

void Union(int x, int y) {
    parent[find_root(x)] = find_root(y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) {
        init();
        cin >> n;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < s.size(); ++j) {
                edges[i][s[j] - 'a'] = 1;
            }
        }

        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (edges[i][k] && edges[j][k]) {
                        Union(i, j);
                        break;
                    }
                }
            }
        }

        set<int> s;
        for (int i = 0; i < n; ++i) {
            s.insert(find_root(i)); // 不可以寫s.insert(parent(i));
        }

        cout << s.size() << endl;
    }
    return 0;
}
