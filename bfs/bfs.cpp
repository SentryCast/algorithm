#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    
    int n;
    int s = 0;

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> n;
    vector< vector <int> > g(n);

    // from adj matrix to adj list
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int num;
            fin >> num;
            if(num != 0)
                g[i].push_back(j);
        }
    }

    queue<int> q;
    q.push(s);
    vector<bool> used(n);
    vector<int> d(n), p(n);
    used[s] = true;
    p[s] = -1;
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for(size_t i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if(!used[to]) {
                used[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
    }

    if(!used[7])
        cout << "No path!" << endl;
    else {
        vector<int> path;
        for(int v = 7; v!=-1; v = p[v])
            path.push_back(v);
        reverse (path.begin(), path.end());
        cout << "Path: ";
        for(size_t i = 0; i < path.size(); ++i)
            cout << path[i] << " ";
    }
}
