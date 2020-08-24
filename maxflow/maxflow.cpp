//Задан ориентированный граф? каждое ребро которого
//обладает целочисленной пропускной способностью.
//Найдите максимальный поток из вершины с номером 1 в вершину
//с номером n
#include <iostream>
#include <fstream>
#include <queue>
 
using namespace std;
 
 
int n, m;
vector<vector<int>> graph;
vector<int> parent;
int result;
 
bool bfs(int s, int t) {
    vector<bool> visited(n);
    queue <int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (int to = 0; to < n; to++) {
            if (!visited[to] && graph[from][to] > 0) {
                q.push(to);
                parent[to] = from;
                visited[to] = true;
            }
        }
    }
    return visited[t];
}
 
void edmondskarp(int s, int t) {
    while (bfs(s, t)) {
        int cf = 1000000000;
        for (int to = t; to != s; to = parent[to]) {
            int from = parent[to];
            cf = min(cf, graph[from][to]);
        }
        for (int to = t; to != s; to = parent[to]) {
            int from = parent[to];
            graph[from][to] -= cf;
            graph[to][from] += cf;
        }
        result += cf;
    }
}
 
int main() {
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");
    fin >> n >> m;
    graph.resize(n, vector<int>(n, 0));
    parent.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int from, to, flow;
        fin >> from >> to >> flow;
        graph[from - 1][to - 1] = flow;
    }
    edmondskarp(0, n - 1);
    fout << result;
    return 0;
}