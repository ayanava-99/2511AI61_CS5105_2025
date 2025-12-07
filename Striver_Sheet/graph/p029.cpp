#include <bits/stdc++.h>
using namespace std;

vector<int> shortest_path_dag_optimal(int total_nodes, vector<vector<pair<int, int>>>& weighted_edges) {
    vector<vector<pair<int, int>>> adj_weighted(total_nodes);
    vector<int> in_degree(total_nodes, 0);

    for (auto& edge : weighted_edges) {
        adj_weighted[edge[0]].push_back({edge[1], edge[2]});
        in_degree[edge[1]]++;
    }

    queue<int> topo_q;
    for (int node = 0; node < total_nodes; node++) {
        if (in_degree[node] == 0) topo_q.push(node);
    }

    vector<int> topo_order;
    while (!topo_q.empty()) {
        int curr = topo_q.front();
        topo_q.pop();
        topo_order.push_back(curr);

        for (auto& [next, wt] : adj_weighted[curr]) {
            in_degree[next]--;
            if (in_degree[next] == 0) topo_q.push(next);
        }
    }

    vector<int> dist(total_nodes, INT_MAX);
    dist[0] = 0;

    for (int node : topo_order) {
        if (dist[node] != INT_MAX) {
            for (auto& [neighbor, weight] : adj_weighted[node]) {
                dist[neighbor] = min(dist[neighbor], dist[node] + weight);
            }
        }
    }

    return dist;
}

int main() {
    vector<vector<pair<int, int>>> edges = {{{{1, 2}, {4, 1}}, {{4, 2}, {2, 3}}, {}, {}, {{5, 4}}, {}}};
    auto dist = shortest_path_dag_optimal(6, edges);
    for (int d : dist) cout << (d == INT_MAX ? -1 : d) << " ";
    cout << endl;
    return 0;
}
