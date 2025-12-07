#include <bits/stdc++.h>
using namespace std;

int count_paths_shortest_optimal(int total_nodes, vector<vector<pair<int, long long>>>& adj_weighted) {
    vector<long long> min_dist(total_nodes, LLONG_MAX);
    vector<long long> path_count(total_nodes, 0);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq_dijkstra;

    min_dist[0] = 0;
    path_count[0] = 1;
    pq_dijkstra.push({0, 0});

    const long long MOD = 1e9 + 7;

    while (!pq_dijkstra.empty()) {
        auto [curr_dist, curr_node] = pq_dijkstra.top();
        pq_dijkstra.pop();

        if (curr_dist > min_dist[curr_node]) continue;

        for (auto [neighbor_node, edge_wt] : adj_weighted[curr_node]) {
            long long new_dist = min_dist[curr_node] + edge_wt;
            if (new_dist < min_dist[neighbor_node]) {
                min_dist[neighbor_node] = new_dist;
                path_count[neighbor_node] = path_count[curr_node];
                pq_dijkstra.push({new_dist, neighbor_node});
            } else if (new_dist == min_dist[neighbor_node]) {
                path_count[neighbor_node] = (path_count[neighbor_node] + path_count[curr_node]) % MOD;
            }
        }
    }
    return path_count[total_nodes - 1];
}

int main() {
    int n = 7;
    vector<vector<pair<int, long long>>> adj = {
        {{6, 7}, {1, 2}, {4, 5}},
        {{2, 3}, {3, 3}},
        {{5, 1}},
        {{5, 1}},
        {{6, 2}},
        {{6, 1}},
        {}
    };
    cout << count_paths_shortest_optimal(n, adj) << endl;
    return 0;
}
