//Назовем циркуляцией поток величины 0. Дан ориентированный граф
//с нижними и верхними пропускными способностями, то есть для
//любых вершин i и j должно быть верно, что l(ij) <= f(ij) <= c(ij),
//где l(ij) - нижняя граница, а c(ij) - верхняя. Требуется найти
//циркуляцию в данном графе, удовлетворяющую данным ограничениям.
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
 
using namespace std;
 
 
vector<vector<int>> answer;
vector<vector<int>> graph;
vector<int> ptr;
vector<int> order;
 
struct Edge {
    int from, to, weight, flow;
};
vector<Edge> edges;
 
 
int n, m, s, t;
 
bool bfs()
{
    order.assign(n, 0);
    queue<int> q;
    q.push(s);
    order[s] = 1;
    while (!q.empty() && !order[t])
    {
        int from = q.front();
        q.pop();
        for (auto& edge : graph[from])
        {
            if (!order[edges[edge].to] && edges[edge].weight > edges[edge].flow)
            {
                q.push(edges[edge].to);
                order[edges[edge].to] = order[from] + 1;
            }
        }
    }
    return order[t];
}
 
int dfs(int vertex = s, int flow = 10000000)
{
    if (!flow)
        return 0;
    if (vertex == t)
        return flow;
    while (ptr[vertex] < graph[vertex].size())
    {
        int edge = graph[vertex][ptr[vertex]];
        if (order[vertex] + 1 == order[edges[edge].to])
        {
            int pushed = dfs(edges[edge].to, min(flow, edges[edge].weight - edges[edge].flow));
            if (pushed)
            {
                edges[edge].flow += pushed;
                edges[edge ^ 1].flow -= pushed;
                return pushed;
            }
        }
        ptr[vertex]++;
    }
    return 0;
}
 
void add(int from, int to, int weight)
{
    graph[from].push_back(edges.size());
    edges.emplace_back(Edge{ from, to, weight, 0});
    graph[to].push_back(edges.size());
    edges.emplace_back(Edge{ to, from, 0, 0 });
}
 
int main()
{
    ifstream fin("circulation.in");
    ofstream fout("circulation.out");
    fin >> n >> m;
    n += 2;
    graph.resize(n);
    ptr.resize(n, 0);
    t = n - 1;
     
    for (int i = 0; i < m; i++)
    {
        int from, to, bottomBorder, topBorder;
        fin >> from >> to >> bottomBorder >> topBorder;
        add(s, to, bottomBorder);
        add(from, to, topBorder - bottomBorder);
        add(from, t, bottomBorder);
    }
    while (bfs())
    {
        while (dfs());
        ptr.assign(n, 0);
    }
    for (int edge : graph[0])
    {
        if (edges[edge].flow < edges[edge].weight)
        {
            fout << "NO\n";
            return 0;
        }
    }
    fout << "YES\n";
    for (int i = 0; i < edges.size(); i += 6)
        fout << edges[i + 2].flow + edges[i + 4].flow << endl;
    return 0;
}