//Гамильтонов путь
#include <iostream>
#include <vector>
#include <fstream>
 
using namespace std;
 
 
vector<vector <int>> alist;
vector<int> way;
vector<bool> visited;
 
 
 
void dfs(int from) {
    visited[from] = true;
    for (int i = 0; i < alist[from].size(); i++) {
        int to = alist[from][i];
        if (!visited[to])
            dfs(to);
    }
    way.push_back(from);
}
 
 
         
bool exist(int from, int to) {
    for (int i = 0; i < alist[from].size(); i++)
        if (alist[from][i] == to)
            return true;
    return false;
}
 
 
 
int main() {
    ifstream fin("hamiltonian.in");
    ofstream fout("hamiltonian.out");
    int n, m;
    fin >> n >> m;
     
    alist.resize(n);
    visited.resize(n);
     
    for (int i = 0; i < m; i++) {
        int from, to;
        fin >> from >> to;
        alist[from - 1].push_back(to - 1);
    }
     
     
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i);
     
     
    for (int i = n - 1; i > 0; i--)
        if (!exist(way[i], way[i - 1])) {
            fout << "NO";
            return 0;
        }
     
     
    fout << "YES";
    fin.close();
    fout.close();
    return 0;
}
