#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <iterator>
#include <string>
#include <sstream>
using namespace std;
using State = vector<int>;
class Pouring
{
private:
    vector<int> _capacities; // {3, 5}
    set<State> _explored;
    set<list<State>> _paths;
    set<list<State>> _solutions;

public:
    Pouring(vector<int> cp): _capacities{cp} { }
    State Empty(State s, int jug_no)
    {
        s[jug_no] = 0;
        return s;
    }
    State Fill(State s, int jug_no)
    {
        s[jug_no] = _capacities[jug_no];
        return s;
    }
    State Pour(State s, int from, int to)
    {
        State t = s;
        int diff = _capacities[to]-s[to];
        if (diff < s[from]) {
            t[to] = _capacities[to];
            t[from] = s[from]-diff;
        } else {
            t[from] = 0;
            t[to] = s[to] + s[from];
        }
        return t;
    }
    set<State> extend(State s)
    {
        set<State> SS;
        for (int i=0; i<_capacities.size(); ++i) {
            SS.insert(Empty(s, i));
            SS.insert(Fill(s, i));
            for (int j=0; j<_capacities.size(); ++j) {
                if (i!=j)
                    SS.insert(Pour(s, i, j));
            }
        }
        return SS;
    }

    void show_state(State s)
    {
        for (auto i : s)
            cout << i << ", " ;
        cout << "->";
    }
    bool found(State s, int target)
    {
        for (auto t : s) {
            if (t==target) return true;
        }
        return false;
        // return any_of(s.cbegin(), s.cend(), [=](int v){ return target==v;});
    }
    void solve(int target, int steps)
    {
        list<State> initialPath;
        initialPath.push_back(State(_capacities.size()));
        _paths.insert(initialPath);

        while (steps > 0) {
            set<list<State>> newPaths;
            set<list<State>> oldPaths;

            for (auto p : _paths) {
                _explored.insert(p.back());
                auto nextStates = extend(p.back());
                for (auto s : nextStates) {
                    if (found(s, target)) {
                        auto np = p;
                        np.push_back(s);
                        _solutions.insert(np);
                    } else {
                    auto search = _explored.find(s);
                    if (search == _explored.cend()) {
                        auto np = p;
                        np.push_back(s);
                        newPaths.insert(np);
                    }
                    }
                }
                oldPaths.insert(p);
            }

            for (auto p : oldPaths) {
                _paths.erase(p);
            }
            for (auto p : newPaths) {
                _paths.insert(p);
            }
            --steps;
        }

    }
    void show_solutions()
    {
        for (auto path : _solutions) {
            for (auto state : path) {
                show_state(state);
            }
            cout << "\n";
        }
    }
};

int main()
{
    vector<int> jugs = {3, 5};
    Pouring problem(jugs);
    problem.solve(4, 6);
    problem.show_solutions();
}