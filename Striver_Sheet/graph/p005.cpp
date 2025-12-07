#include <bits/stdc++.h>
using namespace std;

bool is_bipartite_dfs_optimal(vector<vector<int>>& adj_list) {
    int total_nodes = adj_list.size();
    vector<int> color_array(total_nodes, -1);

    function<bool(int, int)> dfs_color = [&](int curr_node, int color_val) -> bool {
        color_array[curr_node] = color_val;
        for (int neighbor : adj_list[curr_node]) {
            if (color_array[neighbor] == -1) {
                if (!dfs_color(neighbor, 1 - color_val)) return false;
            } else if (color_array[neighbor] == color_val) {
                return false;
            }
        }
        return true;
    };

    for (int start_node = 0; start_node < total_nodes; start_node++) {
        if (color_array[start_node] == -1) {
            if (!dfs_color(start_node, 0)) return false;
        }
    }
    return true;
}

int main() {
    vector<vector<int>> adj1 = {{1}, {0, 2}, {1}};
    cout << (is_bipartite_dfs_optimal(adj1) ? 1 : 0) << endl;
    return 0;
}
