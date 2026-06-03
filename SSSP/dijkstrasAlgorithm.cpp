#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adjList, int source) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    vector<int> dist(V, INT_MAX);

    dist[source] = 0;
    pq.push({0, source});

    while(!pq.empty()) {
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (auto& edge : adjList[u]) {
            int v = edge.first;
            int edge_weight = edge.second;

            if (dist[u] + edge_weight < dist[v]) {
                dist[v] = dist[u] + edge_weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int V = 3;
    vector<vector<pair<int, int>>> adjList(V);

    adjList[0].push_back({1, 2});
    adjList[1].push_back({0, 2});

    adjList[1].push_back({2, 4});
    adjList[2].push_back({1, 4});

    adjList[0].push_back({2, 3});
    adjList[2].push_back({0, 3});

    int source = 0;
    vector<int> shortest_distances = dijkstra(V, adjList, source);

    cout << "Shortest distances from source node " << source << ":" << endl;
    for (int i = 0; i < V; i++) {
        cout << "To node " << i << " -> " << shortest_distances[i] << endl;
    }

    return 0;
}