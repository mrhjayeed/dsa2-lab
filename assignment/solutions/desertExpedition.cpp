#include <bits/stdc++.h>
using namespace std;

int dijkstra(int N, int K, vector<vector<pair<int, int>>>& adjList, int src, int dst, vector<bool>& isDepot) {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    vector<vector<int>> dist(N + 1, vector<int>(K + 1, INT_MAX));

    dist[src][K] = 0;
    pq.push({0, {src, K}});

    while(!pq.empty()) {
        int current_cost = pq.top().first;
        int u = pq.top().second.first;
        int current_fuel = pq.top().second.second;
        pq.pop();

        if (u == dst) return current_cost;

        if (current_cost > dist[u][current_fuel]) continue;

        for (auto& edge : adjList[u]) {
            int v = edge.first;
            int edge_weight = edge.second;

            if (current_fuel >= edge_weight) {
                int next_fuel = current_fuel - edge_weight;

                if (isDepot[v]) {
                    next_fuel = K;
                }

                int next_cost = current_cost + edge_weight;

                if (next_cost < dist[v][next_fuel]) {
                    dist[v][next_fuel] = next_cost;
                    pq.push({next_cost, {v, next_fuel}});
                }
            }
        }
    }

    return -1;
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    int src, dst;
    cin >> src >> dst;

    int F;
    cin >> F;

    vector<bool> isDepot(N + 1, false);
    for (int i = 0; i < F; i++) {
        int depot_node;
        cin >> depot_node;
        isDepot[depot_node] = true;
    }
    
    vector<vector<pair<int, int>>> adjList(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w}); 
    }

    int res = dijkstra(N, K, adjList, src, dst, isDepot);

    cout << res << endl;

    return 0;
}