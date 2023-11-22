#include <iostream>
using namespace std;

int main(){
	int n, m, A, ans = (int)((1u << 31)-1); // large number
    cin >> n >> m;
	for(int i = 0; i < n*m; ++i){
    	cin >> A;
        ans = (A < ans)?A:ans;
    }
	cout << ans << endl;
    return 0;
}