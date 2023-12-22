#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

map<int, map<char, vector<string>>> bucket;

int countnum(string& s){
	return count_if(s.begin(), s.end(), [](char c){ return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; });
}

char countlast(string& s){
	return *(find_if(s.rbegin(), s.rend(), [](char c){ return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }));
}

int main(){
	int n; cin >> n;
    while(n--){
    	string s; cin >> s; 
        bucket[countnum(s)][countlast(s)].emplace_back(s);
    }
    
    int comp = 0, uncomp = 0;
    for(auto [x, y]: bucket){
    	for(auto [w, v]: y){
        	comp += v.size()/2;
        }
        int tmp = 0;
        for(auto [w, v]: y){
        	tmp += v.size()%2;
        }
        uncomp += tmp/2;
    }
    
    int ans = min(comp, uncomp);
    int diff = comp - uncomp;
    ans += ( diff >= 2 )? diff/2: 0;
    cout << ans << endl;
    
	return 0;
}