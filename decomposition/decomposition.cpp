//Найдите максимальный поток из вершины с номером 1 в вершину с
//номером n и постройте декомпозицию этого потока.
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
 
using namespace std;
 
vector<vector<int>> answer;
vector<vector<int>> graph;
vector<int> ptr;
vector<int> order;
 
int n , m, s, t;
 
struct Edge {
    int from, to, weight, flow, number;
};
vector<Edge> edges;
 
int dfs(int v = s, int flow = 10000000) {
    if (!flow)
        return 0;
    if (v == t)
        return flow;
    while (ptr[v] < graph[v].size()) {
        int edge = graph[v][ptr[v]];
        if (order[v] + 1 == order[edges[edge].to]){
            int pushed = dfs(edges[edge].to, min(flow, edges[edge].weight - edges[edge].flow));
            if (pushed) {
                edges[edge].flow += pushed;
                edges[edge ^ 1].flow -= pushed;
                return pushed;
            }
        }
        ptr[v]++;
    }
    return 0;
}
 
bool bfs() {
    order.assign(n, 0);
    queue<int> q;
    q.push(s);
    order[s] = 1;
    while (!q.empty() && !order[t]) {
        int from = q.front();
        q.pop();
        for (auto& edge : graph[from]) {
            if (!order[edges[edge].to] && edges[edge].weight > edges[edge].flow) {
                q.push(edges[edge].to);
                order[edges[edge].to] = order[from] + 1;
            }
        }
    }
    return order[t];
}
 
int decomposition(int v, int minFlow = 10000000) {
    if (v == t) {
        answer.emplace_back();
        return minFlow;
    }
    for (int edge : graph[v]) {
        if (edges[edge].flow > 0) {
            int result = decomposition(edges[edge].to, min(minFlow, edges[edge].flow));
            if (result) {
                answer.back().push_back(edges[edge].number);
                if (v == s) {
                    answer.back().push_back(answer[answer.size() - 1].size());
                    answer.back().push_back(result);
                    reverse(answer.back().begin(), answer.back().end());
                }
                edges[edge].flow -= result;
                return result;
            }
        }
    }
    return 0;
}
 
int main() {
    ifstream fin("decomposition.in");
    ofstream fout("decomposition.out");
    fin >> n >> m;
    graph.resize(n);
    ptr.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        fin >> from >> to >> weight;
        graph[from - 1].push_back(edges.size());
        edges.emplace_back(Edge{from - 1, to - 1, weight, 0, i + 1});
        graph[to - 1].push_back(edges.size());
        edges.emplace_back(Edge{to - 1, from - 1, 0, 0, i + 1});
    }
    t = n - 1;
    while (bfs()) {
        while (dfs());
        ptr.assign(n, 0);
    }
    while (decomposition(s));
    fout << answer.size() << "\n";
    for (auto& i : answer) {
        for (auto& j : i)
            fout << j << ' ';
        fout << endl;
    }
    return 0;
}