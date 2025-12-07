#include <bits/stdc++.h>
using namespace std;

bool has_cycle_undirected_dfs_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    vector<bool> visited_node(total_nodes, false);

    function<bool(int, int)> dfs_check_cycle = [&](int curr_node, int parent_node) -> bool {
        visited_node[curr_node] = true;
        for (int neighbor : adj_list[curr_node]) {
            if (!visited_node[neighbor]) {
                if (dfs_check_cycle(neighbor, curr_node)) return true;
            } else if (neighbor != parent_node) {
                return true;
            }
        }
        return false;
    };

    for (int start_node = 0; start_node < total_nodes; start_node++) {
        if (!visited_node[start_node]) {
            if (dfs_check_cycle(start_node, -1)) return true;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> adj = {{1}, {0, 2}, {1, 3}, {2}, {5}, {4, 6}, {5}};
    cout << (has_cycle_undirected_dfs_optimal(7, adj) ? "Yes" : "No") << endl;
    return 0;
}
