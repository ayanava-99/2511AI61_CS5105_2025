#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra_pq_optimal(int total_nodes, vector<vector<pair<int, int>>>& adj_weighted, int source_node) {
    vector<int> min_dist(total_nodes, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_dist;

    min_dist[source_node] = 0;
    pq_dist.push({0, source_node});

    while (!pq_dist.empty()) {
        auto [curr_dist, curr_node] = pq_dist.top();
        pq_dist.pop();

        if (curr_dist > min_dist[curr_node]) continue;

        for (auto [neighbor_node, edge_weight] : adj_weighted[curr_node]) {
            int new_dist = min_dist[curr_node] + edge_weight;
            if (new_dist < min_dist[neighbor_node]) {
                min_dist[neighbor_node] = new_dist;
                pq_dist.push({new_dist, neighbor_node});
            }
        }
    }
    return min_dist;
}

int main() {
    int nodes = 3;
    vector<vector<pair<int, int>>> adj = {{{1, 1}, {2, 6}}, {{2, 3}, {0, 1}}, {{1, 3}, {0, 6}}};
    auto res = dijkstra_pq_optimal(nodes, adj, 2);
    for (int d : res) cout << d << " ";
    cout << endl;
    return 0;
}
