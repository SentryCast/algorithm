//Топологическая сортировка
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
 
enum Color {
    white,
    gray,
    black
};
 
vector<vector<int>> alist;
vector<int> color;
vector<int> ans;
bool cycle = false;
 
 
void dfs(int v) {
    color[v] = gray;
    for(int i = 0; i < alist[v].size(); i++) {
        int to = alist[v][i];
        if(color[to] == white)
            dfs(to);
        if(color[to] == gray) {
            cycle = true;
            return;
        }
    }
    color[v] = black;
    ans.push_back(v);
}
 
 
void topsort() {
    for(int i = 1; i < alist.size(); i++)
        color[i] = white;
    ans.clear();
    for(int i = 1; i < alist.size(); i++) {
        if(color[i] == white) {
            dfs(i);
        }
    }
}
 
int main() {
     
    ifstream fin("topsort.in");
    ofstream fout("topsort.out");
     
    int n, m;
    fin >> n >> m;
     
    alist.resize(n+1);
    color.resize(n+1);
    ans.resize(n+1);
     
    for(int i = 1; i <= m; i++) {
        int col1, col2;
        fin >> col1 >> col2;
        alist[col1].push_back(col2);
    }
    topsort();
    if(cycle) {
        fout << "-1" << endl;
    } else {
        for(int i = n-1; i >= 0; i--) {
            fout << ans[i] << " ";
        }
    }
     
    fin.close();
    fout.close();
    return 0;
}