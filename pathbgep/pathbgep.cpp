//Найти кратчайшее расстояние от первой вершин
//до всех вершин во взвешенном графе
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;
const int INF = 100000000;
 
vector <vector <pair <int, int>>> graph;
vector <int> dst;
set <pair<int, int>> beforeEdges;
 
void dkst() {
    dst[0] = 0;
    beforeEdges.emplace(dst[0], 0);
    while (!beforeEdges.empty()) {
        int from = beforeEdges.begin()->second;
        beforeEdges.erase(beforeEdges.begin());
        for (auto& edge : graph[from]) {
            int to = edge.first;
            int weight = edge.second;
            if (dst[from] + weight < dst[to]) {
                beforeEdges.erase({dst[to], to});
                dst[to] = dst[from] + weight;
                beforeEdges.emplace(dst[to], to);
            }
        }
    }
}
 
int main() {
    ifstream fin("pathbgep.in");
    ofstream fout("pathbgep.out");
    int n, m;
    fin >> n >> m;
    graph.resize(n);
    dst.resize(n, INF);
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        fin >> from >> to >> weight;
        graph[from - 1].emplace_back(to - 1, weight);
        graph[to - 1].emplace_back(from - 1, weight);
    }
    dkst();
    for (int weight : dst)
        fout << weight << " ";
    return 0;
}