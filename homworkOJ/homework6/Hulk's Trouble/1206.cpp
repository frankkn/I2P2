#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int n; cin >> n;
	vector<int> a; a.assign(n, 0);
    for(int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());
    int q; cin >> q;
    while(q--){
        int x; cin >> x;
    	cout << distance(lower_bound(a.begin(), a.end(), x), upper_bound(a.begin(), a.end(), x)) << endl;
    }
	return 0;
}