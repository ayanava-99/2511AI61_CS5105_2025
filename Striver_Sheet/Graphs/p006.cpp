#include <bits/stdc++.h>
using namespace std;

// Dijkstra's Algorithm using Priority Queue
vector<int> dijkstra(int v, vector<vector<pair<int, int>>>& adj, int src) {
    vector<int> dist(v, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int v, e, src;
    cout << "Enter V, E, Source: ";
    cin >> v >> e >> src;

    vector<vector<pair<int, int>>> adj(v);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> result = dijkstra(v, adj, src);
    cout << "Distances: ";
    for (int d : result) {
        cout << d << " ";
    }
    cout << "\nTime: O((V+E)logV), Space: O(V)" << endl;

    return 0;
}
