#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> bridges_optimal(int total_nodes, vector<vector<int>>& connections) {
    vector<vector<int>> adj_list(total_nodes);
    for (auto& conn : connections) {
        adj_list[conn[0]].push_back(conn[1]);
        adj_list[conn[1]].push_back(conn[0]);
    }

    vector<int> disc_time(total_nodes, -1), low_time(total_nodes, -1);
    vector<vector<int>> result_bridges;
    int timer_val = 0;

    function<void(int, int)> dfs_find_bridges = [&](int u, int parent_node) {
        disc_time[u] = low_time[u] = timer_val++;

        for (int v : adj_list[u]) {
            if (disc_time[v] == -1) {
                dfs_find_bridges(v, u);
                low_time[u] = min(low_time[u], low_time[v]);

                if (low_time[v] > disc_time[u]) {
                    result_bridges.push_back({u, v});
                }
            } else if (v != parent_node) {
                low_time[u] = min(low_time[u], disc_time[v]);
            }
        }
    };

    for (int node = 0; node < total_nodes; node++) {
        if (disc_time[node] == -1) {
            dfs_find_bridges(node, -1);
        }
    }

    return result_bridges;
}

int main() {
    vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    auto bridges = bridges_optimal(4, connections);
    for (auto& bridge : bridges) {
        cout << bridge[0] << " " << bridge[1] << endl;
    }
    return 0;
}
