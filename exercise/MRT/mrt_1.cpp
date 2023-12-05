#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

using Graph = map<string,set<string>>;
using Path = list<string>;

Path has_path(Graph &g, string src, string dst, Path path, Path best_path)
{
    if (src==dst) {
        path.push_back(dst);
        if (best_path.empty())
            return path;
        else if (path.size() < best_path.size())
            return path;
        else
            return best_path;
    }

    path.push_back(src);

    for (auto& n: g[src]) {
        if (find(path.begin(), path.end(), n) == path.end() ) // not in path
            best_path = has_path(g, n, dst, path, best_path); // recursive
    }
    return best_path;
}


int main()
{
    ifstream fin;
    fin.open("mrt.txt");

    Graph mrt_graph;

    string dep, arv;
    while (fin >> dep) {
        fin >> arv;
        arv.erase(0, 6); // remove the starting characters "捷運" utf-8下，一個中文佔3個字節
        dep.erase(0, 6);
        mrt_graph[dep].insert(arv);  // one copy for each element
        mrt_graph[arv].insert(dep);
    }
    fin.close();

    /*
    int i=1;
    for (auto& v: mrt_graph) {
        for (auto& t: v.second) {
            cout << i++ << ":" << v.first << "-->" << t << endl;
        }
    }
    */

    Path p, bp; // empty list
    bp = has_path(mrt_graph, "內湖站", "小南門站", p, bp);
    for (auto &r: bp) {
        cout << r << "-->" ;
    }
    cout << endl;
}