//Конденсация графа
#include <iostream>
#include <vector>
#include <fstream>
 
using namespace std;
 
vector<vector <int>> alist;
vector<vector <int>> transposed;
vector<int> topsort;
vector<int> component;
vector<bool> visited;
 
int componentCount = 1;
 
 
void dfs(int from) {
    visited[from] = true;
    for (int i = 0; i < alist[from].size(); i++) {
        int to = alist[from][i];
        if (!visited[to])
            dfs(to);
    }
    topsort.push_back(from);
}
 
 
 
void transdfs(int from) {
    visited[from] = true;
    component[from] = componentCount;
    for (int i = 0; i < transposed[from].size(); i++) {
        int to = transposed[from][i];
        if (!visited[to])
            transdfs(to);
    }
}
 
int main() {
     
     
    ifstream fin("cond.in");
    ofstream fout("cond.out");
     
     
    int n, m;
    fin >> n >> m;
     
    transposed.resize(n);
    alist.resize(n);
    visited.resize(n, false);
    component.resize(n);
     
    for (int i = 0; i < m; i++) {
        int from, to;
        fin >> from >> to;
        alist[from - 1].push_back(to - 1);
        transposed[to - 1].push_back(from - 1);
    }
     
     
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i);
    visited.assign(n, false);
     
     
    for (int i = 0; i < n; i++) {
        int v = topsort[n - 1 - i];
        if (!visited[v]) {
            transdfs(v);
            componentCount++;
        }
    }
    fout << componentCount - 1 << endl;
     
     
    for (int i = 0; i < n; i++)
        fout << component[i] << " ";
    fin.close();
    fout.close();
    return 0;
}