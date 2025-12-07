#include <bits/stdc++.h>
using namespace std;

int count_provinces_optimal(vector<vector<int>>& adj_matrix) {
    int total_nodes = adj_matrix.size();
    vector<bool> visited_node(total_nodes, false);
    int province_count = 0;

    function<void(int)> dfs_traverse = [&](int curr_idx) {
        visited_node[curr_idx] = true;
        for (int neighbor_idx = 0; neighbor_idx < total_nodes; neighbor_idx++) {
            if (adj_matrix[curr_idx][neighbor_idx] == 1 && !visited_node[neighbor_idx]) {
                dfs_traverse(neighbor_idx);
            }
        }
    };

    for (int start_idx = 0; start_idx < total_nodes; start_idx++) {
        if (!visited_node[start_idx]) {
            province_count++;
            dfs_traverse(start_idx);
        }
    }
    return province_count;
}

int main() {
    vector<vector<int>> adj_matrix = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    cout << count_provinces_optimal(adj_matrix) << endl;
    return 0;
}
