#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

// g++ test.cpp -o test -std=c++1z
// ./test

class GuessNumber {
public:
    GuessNumber() {
        rng = mt19937(random_device{}()); //random number generator

        // 產生所有可能的答案(0000~9999)
	    for (int i=0; i<10000; i++) {
		    stringstream os;
		    os << setfill('0') << setw(4) << i;
		    solutions.push_back(os.str());
        }
        // // 去除不可能的答案(有重複數字，例如: 1123)
	    solutions.erase(remove_if(solutions.begin(), solutions.end(), // // remove_if 會回傳一個 iterator，指向最後一個不應該被移除的元素的下一個位置
	    [](string& s) {
		    for (int j=0; j<4; ++j)
			    for (int k=0; k<j; ++k)
				    if (s[j]==s[k]) return true;
		    return false;
	    }), solutions.end());
    }

    // 去除不可能的答案
    void trim(int A, int B) {
        string cur = my_guess;
        solutions.erase(remove_if(solutions.begin(), solutions.end(),
        [=](string& str) { // = 代表可以使用外部的變數: A, B, cur
            int AA=A, BB=B;
            for (int j=0; j<4; ++j) {
                if (str[j]==cur[j]) --AA; // 答案的數字和位置都對，則 AA 減一
                for (int k=0; k<4; ++k)
                    if (j!=k&&str[j]==cur[k]) --BB; // 答案的數字對，但位置不對，則 BB 減一
            }
            if (AA==0 && BB==0) return false; // AA 和 BB 都是 0，代表這個答案是可能的
            else return true; // 要淘汰的答案所以回傳 true
        }), solutions.end());
    }

    string guess() {
        uniform_int_distribution<>dis(0, size()-1); // 產生一個隨機數字，範圍是 0 到 size()-1
        my_guess = solutions[dis(rng)]; // 隨機選一個答案
        return my_guess;
    }

    size_t size() {
        return solutions.size();
    }

    void show() {
        for (auto s: solutions)
            cout << s << endl;
    }

private:
    mt19937 rng; // random number generator
    string my_guess;
    vector<string> solutions;
};

int main() {
    GuessNumber gn;

	while (gn.size()>1) {
		cout << gn.guess() << endl;
		cout << "? A ? B" << endl;
		int A, B;
		cin >> A >> B;

		gn.trim(A, B);
		if (gn.size()<10) {
		    cout << "------" << endl;
		    gn.show();
		    cout << "------" << endl;
        }

        if (gn.size()==1) {
            cout << "I got it!" << endl;
            gn.show();
        }
        if (gn.size()==0)
            cout << "No way!" << endl;
	}
}
