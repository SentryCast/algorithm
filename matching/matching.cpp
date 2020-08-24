//Дан двудольный невзвешенный граф. Необходимо найти максимальное
//паросочетание.
#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int n, m, k;
vector <vector<int>> graph;
vector<int> max_match;
 
vector<bool> visited;
vector<bool> used;
 
bool kuhn(int from)
{
    if (visited[from])
        return false;
    visited[from] = true;
    for (int i = 0; i < graph[from].size(); i++)
    {
        int to = graph[from][i];
        if (max_match[to] == -1 || kuhn(max_match[to]))
        {
            max_match[to] = from;
            return true;
        }
    }
    return false;
}
 
int main() {
    ifstream fin("matching.in");
    ofstream fout("matching.out");
    fin >> n >> m >> k;
    graph.resize(n, vector<int>());
    max_match.resize(m, -1);
    used.resize(n);
    visited.resize(n);
    for (int i = 0; i < k; i++)
    {
        int from, to;
        fin >> from >> to;
        graph[from - 1].push_back(to - 1);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < graph[i].size(); j++)
            if (max_match[graph[i][j]] == -1)
            {
                max_match[graph[i][j]] = i;
                used[i] = true;
                break;
            }
    for (int i = 0; i < n; i++)
    {
        if (used[i])
            continue;
        for (int j = 0; j < n; j++)
            visited[j] = false;
        kuhn(i);
    }
    int result = 0;
    for (int i = 0; i < m; i++)
        if (max_match[i] != -1)
            result++;
    fout << result;
    return 0;
}