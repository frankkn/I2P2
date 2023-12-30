#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

vector<string> a; // 用來存數字
map<string, int> mp; // 用來存某個數字出現了幾次

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
    // a.assign(n+1, "");
    string MAX = "", MIN = "";
    while(n--){
    	string op; cin >> op;
        if(op == "insert"){
        	string num; cin >> num;
            a.emplace_back(num);
            mp[num]++;
            if(a.size() == 1){ MAX = MIN = num; continue; } 
            if(num.size() > MAX.size())	MAX = num;
            else if(num.size() == MAX.size() && num > MAX)	MAX = num;
            if(num.size() < MIN.size()) MIN = num;
            else if(num.size() == MIN.size() && num < MIN)	MIN = num;
        }else if(op == "find"){
            int idx; cin >> idx;
            if(idx >= a.size())	continue;
            cout << a[idx-1] << '\n';        
        }else if(op == "min"){
            if(MIN == "")	continue;
        	cout << MIN << '\n';
        }else if(op == "max"){
            if(MAX == "")	continue;
        	cout << MAX << '\n';
        }else if(op == "amount"){
        	string num; cin >> num;
            if(mp.find(num) != mp.end()){
            	cout << mp[num] << '\n';
            }else{
            	cout << "0" << '\n'; 
            }
        }
    }
	return 0;
}