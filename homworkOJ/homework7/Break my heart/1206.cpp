#include <iostream>
#include <set>
#include <string>
#include <algorithm>
using namespace std;
using ll = long long;

int main(){
	int n; cin >> n;
    set<int> s;
    ll sum = 0;
    while(n--){
    	string op; cin >> op;
    	if(op == "insert"){
        	int x; cin >> x;
            if(s.find(x) == s.end()){
            	s.insert(x);
                sum += x;
            }
        }else if(op == "print"){
            if(s.empty()) continue;
            auto ij = prev(s.end());
        	for(auto it= s.begin(); it != s.end(); it++){
            	cout << (*it) << (it == ij?"\n":" ");
            }
        }else if(op == "min"){
            if(s.empty()) continue;
        	cout << (*s.begin()) << endl;
        }else if(op == "range_erase"){
        	int l, r; cin >> l >> r;
            if(s.empty()) continue;
            auto L = s.lower_bound(l), R = s.upper_bound(r);
            for(auto it = L; it != R; it++){
                sum -= *it;
            }
            s.erase(L, R);
        }else if(op == "sum"){
        	cout << sum << endl;          
        }
    }
	return 0;
}