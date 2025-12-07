#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra_set_optimal(int total_nodes, vector<vector<pair<int, int>>>& adj_weighted, int source_node) {
    vector<int> min_dist(total_nodes, INT_MAX);
    set<pair<int, int>> dist_set;

    min_dist[source_node] = 0;
    dist_set.insert({0, source_node});

    while (!dist_set.empty()) {
        auto [curr_dist, curr_node] = *dist_set.begin();
        dist_set.erase(dist_set.begin());

        if (curr_dist > min_dist[curr_node]) continue;

        for (auto& [neighbor, weight] : adj_weighted[curr_node]) {
            int new_dist = min_dist[curr_node] + weight;
            if (new_dist < min_dist[neighbor]) {
                dist_set.erase({min_dist[neighbor], neighbor});
                min_dist[neighbor] = new_dist;
                dist_set.insert({new_dist, neighbor});
            }
        }
    }

    return min_dist;
}

int main() {
    vector<vector<pair<int, int>>> adj = {{{1, 1}, {2, 6}}, {{2, 3}, {0, 1}}, {{1, 3}, {0, 6}}};
    auto dist = dijkstra_set_optimal(3, adj, 2);
    for (int d : dist) cout << d << " ";
    cout << endl;
    return 0;
}
