//В связном графе найти остовное дерево минимального веса
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
 
vector <bool> used;
vector <pair <long long, long long>> graph[1000000];
 
 
 
long long prim() {
    long long mst_weight = 0;
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> q;
    q.push(make_pair(0, 0));
    while (!q.empty()) {
        pair<long long, long long> vertexWeight = q.top();
        q.pop();
        long long dst = vertexWeight.first;
        long long v = vertexWeight.second;
        if (used[v])
            continue;
        used[v] = true;
        mst_weight += dst;
        for (long long i = 0; i < graph[v].size(); i++) {
            long long u = graph[v][i].first;
            long long len = graph[v][i].second;
            if (!used[u])
                q.push(make_pair(len, u));
        }
    }
    return mst_weight;
}
 
 
 
 
int main() {
    ifstream fin("spantree3.in");
    ofstream fout("spantree3.out");
    long long vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    used.resize(vertexNum, false);
    for (long long i = 0; i < edgeNum; i++) {
        long long from, to, weight;
        fin >> from >> to >> weight;
        graph[from - 1].push_back(make_pair(to - 1, weight));
        graph[to - 1].push_back(make_pair(from - 1, weight));
    }
     
     
    fout << prim() << endl;
     
    return 0;
}