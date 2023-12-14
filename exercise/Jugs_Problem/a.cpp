#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

using State = vector<int>;
using Path = list<State>;

class Pouring
{
 public:
  Pouring(vector<int> v): _capacities{v} {}

  State Empty(int idx, State s)
  {
    s[idx] = 0;
    return s;
  }

  State Fill(int idx, State s)
  {
    s[idx] = _capacities[idx];
    return s;
  }

  State Pour(int src, int tgt, State s)
  {
    int diff = _capacities[tgt] - s[tgt];
    if (s[src] > diff) {
      s[tgt] = _capacities[tgt];
      s[src] = s[src] - diff;
    } else {
      s[tgt] = s[tgt] + s[src];
      s[src] = 0;
    }
    return s;
  }

  set<State> extend(State s) {
    set<State> S;
    for (int i=0; i<_capacities.size(); ++i) {
      S.insert(Empty(i, s));
      S.insert(Fill(i, s));
      for (int j=0; j<_capacities.size(); ++j) {
        if (i!=j) {
          S.insert(Pour(i, j, s));
        }
      }
    }
    return S;
  }

  bool found(State s, int goal) {
    return any_of(s.cbegin(), s.cend(), [goal](int x) { return x==goal;});
  }

  void solve(int goal, int steps) {
    Path initialPath;
    initialPath.push_back(State(_capacities.size()));
    _paths.insert(initialPath);

    while (steps > 0) {
      set<Path> newPaths;

      for (const auto & p: _paths) {
        _explored.insert(p.back()); // p.back() is a State   p is a list of States
        auto nextStates = extend(p.back());
        for (const auto &s : nextStates) {
          if (found(s, goal)) {
            auto np = p;
            np.push_back(s);
            _solutions.insert(np);
          } else {
              if (_explored.find(s) == _explored.cend()) {
                auto np = p;
                np.push_back(s);
                newPaths.insert(np);
              }
          }
        }
      }
      _paths = newPaths;
      --steps;
    }
  }

  void show_solutions() {
      for (const auto& p: _solutions) {
          for (const auto& s: p) {
              cout << "(";
              for (const auto& x: s) {
                cout << x << ", ";
              }
              cout << ") -> ";
          }
          cout << "\n";
      }
  }


 private:
  vector<int> _capacities;
  set<Path> _solutions;
  set<Path> _paths;
  set<State> _explored;
};

int main()
{
  vector<int> jugs{3, 4, 7};
  Pouring problem{jugs};
  problem.solve(5, 6);
  problem.show_solutions();
}