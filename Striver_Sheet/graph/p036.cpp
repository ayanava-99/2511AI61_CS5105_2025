#include <bits/stdc++.h>
using namespace std;

int prim_mst_optimal(int total_nodes, vector<vector<pair<int, int>>>& adj_weighted) {
    vector<bool> visited_node(total_nodes, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_edge;

    pq_edge.push({0, 0});
    int mst_weight = 0;

    while (!pq_edge.empty()) {
        auto [weight, u] = pq_edge.top();
        pq_edge.pop();

        if (visited_node[u]) continue;
        visited_node[u] = true;
        mst_weight += weight;

        for (auto& [v, wt] : adj_weighted[u]) {
            if (!visited_node[v]) {
                pq_edge.push({wt, v});
            }
        }
    }

    return mst_weight;
}

int main() {
    vector<vector<pair<int, int>>> adj = {{{1, 2}, {3, 6}}, {{0, 2}, {2, 3}, {3, 8}, {4, 5}}, {{1, 3}, {4, 7}}, {{0, 6}, {1, 8}}, {{1, 5}, {2, 7}}};
    cout << prim_mst_optimal(5, adj) << endl;
    return 0;
}
