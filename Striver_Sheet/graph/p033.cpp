#include <bits/stdc++.h>
using namespace std;

vector<int> bellman_ford_optimal(int total_nodes, vector<vector<int>>& edges_list, int src) {
    vector<int> dist(total_nodes, INT_MAX);
    dist[src] = 0;

    for (int relax_count = 0; relax_count < total_nodes - 1; relax_count++) {
        for (auto& edge : edges_list) {
            if (dist[edge[0]] != INT_MAX && dist[edge[0]] + edge[2] < dist[edge[1]]) {
                dist[edge[1]] = dist[edge[0]] + edge[2];
            }
        }
    }

    for (auto& edge : edges_list) {
        if (dist[edge[0]] != INT_MAX && dist[edge[0]] + edge[2] < dist[edge[1]]) {
            return vector<int>{-1};
        }
    }

    return dist;
}

int main() {
    vector<vector<int>> edges = {{3, 2, 6}, {5, 3, 1}, {0, 1, 5}, {1, 5, -3}, {1, 2, -2}, {3, 4, -2}, {2, 4, 3}};
    auto dist = bellman_ford_optimal(6, edges, 0);
    for (int d : dist) cout << (d == INT_MAX ? -1 : d) << " ";
    cout << endl;
    return 0;
}
