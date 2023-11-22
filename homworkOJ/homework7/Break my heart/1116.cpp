#include <iostream>
#include <set>
#include <cassert>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    set<int> s;
    int n; cin >> n;
    ll sum = 0;
    while(n--){
        string op;
        cin >> op;
        if(op == "insert"){
            int a; cin >> a;
            if(s.find(a) == s.end()){
                sum += a;
                s.insert(a);
            }
            // if(s.insert(a).second) sum += num;
        }else if(op == "print"){
            if(s.empty()) continue;
            auto last = s.end();
            last--;
            for(auto it = s.begin(); it != s.end(); it++){
                cout << *it << ((it == last)? '\n':' ');
            }
        }else if(op == "min"){
            if(s.empty()) continue;
            cout << *s.begin() << "\n";
        }else if(op == "range_erase"){
            int l, r; cin >> l >> r;
            auto L = s.lower_bound(l), R = s.upper_bound(r);
            for(auto it = L; it != R; it++){
                sum -= (*it);
            }
            s.erase(L, R);
        }else if(op == "sum"){
            cout << sum << "\n";
        }/*else{
            assert(false);
        }*/
    }
    return 0;
}