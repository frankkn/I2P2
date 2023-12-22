#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
猜電腦「心裡想」的數字:使用者猜電腦的「腦中」想的數字。
做法是先讓使用者輸入猜測的字串，然後試過所以可能的 ?A?B 的組合，看看哪一種狀況對使用者最不利，就答覆那一種 ?A?B。
所謂最不利的狀況，就是只被刪去的不可能答案最少。
也就是說，我們希望找到某一種 ?A?B 的狀況，使得當我們用 trim 把不符合的字串刪去之後，剩餘的 solutions 越多越好。
基於這樣的做法，使用者需要猜測的次數應該會很多，
因為不管怎麼猜，每次都會得到最差的 ?A?B 的答覆，能夠用來消去的線索最少。
*/

class GuessMyNumber {
public:
    GuessMyNumber() {
	    for (int i=0; i<10000; i++) {
		    stringstream os;
		    os << setfill('0') << setw(4) << i;
		    solutions.push_back(os.str());
        }
	    solutions.erase(remove_if(solutions.begin(), solutions.end(),
	    [](string& s) {
		    for (int j=0; j<4; ++j)
			    for (int k=0; k<j; ++k)
				    if (s[j]==s[k]) return true;
		    return false;
	    }), solutions.end());
    }
    vector<string> trim(int A, int B, string cur) {
        vector<string> sols{solutions}; // 複製5040個數字(solutions)
		sols.erase(remove_if(sols.begin(), sols.end(),
		[=](string& str) {
            int AA=A, BB=B;
			for (int j=0; j<4; ++j) {
			    if (str[j]==cur[j]) --AA;
				for (int k=0; k<4; ++k)
					if (j!=k&&str[j]==cur[k]) --BB;
            }
            if (AA==0 && BB==0) return false;
			else return true;
		}), sols.end());
		return sols;
    }
    void set_solutions(vector<string> &sols)
    {
        solutions = sols;
    }
    size_t size() {
        return solutions.size();
    }
    void show() {
        for (auto s: solutions)
            cout << s << endl;
    }
private:
    vector<string> solutions;
};
int main() {
    GuessMyNumber gn;
    int maxguess = 8;
	while (gn.size()>0 && maxguess-->0) {
        cout << "Your guess: ";
        string guess;
        cin >> guess;
        vector<string> best_sols;
        int bestA=0, bestB=0;
        for (int A=0; A<=4; ++A) {
            for (int B=0; B<=4-A; ++B) {
                vector<string> sols = gn.trim(A,B,guess);
                if (best_sols.size()<sols.size()) {
                    best_sols = sols;
                    bestA = A;
                    bestB = B;
                }
            }
        }
        gn.set_solutions(best_sols);
        cout << bestA << "A" << bestB << "B" << endl;

        if (gn.size()==0) {
            cout << "You got it!" << endl;
        } else if (gn.size()<20) {
            cout << "-----" << endl;
            cout << "Hint:" << endl;
            gn.show();
            cout << "-----" << endl;
        }
	}
}