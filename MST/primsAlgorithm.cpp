#include <bits/stdc++.h>
using namespace std;

int spanningTree(int V, vector<vector<pair<int, int>>>& adjList) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    vector<bool> visited(V, false);

    pq.push({0, 0});

    int mst_weight = 0;

    while(!pq.empty()) {
        int wt = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;
        mst_weight += wt;

        for (auto& edge : adjList[u]) {
            int v = edge.first;
            int edge_weight = edge.second;

            if (!visited[v]) pq.push({edge_weight, v});
        }
    }

    return mst_weight;
}

int main() {
    int V= 3;
    vector<vector<pair<int, int>>> adjList(V);

    adjList[0].push_back({1, 2});
    adjList[1].push_back({0, 2});

    adjList[1].push_back({2, 4});
    adjList[2].push_back({1, 4});

    adjList[0].push_back({2, 3});
    adjList[2].push_back({0, 3});

    cout << spanningTree(V, adjList) << endl;

    return 0;
}