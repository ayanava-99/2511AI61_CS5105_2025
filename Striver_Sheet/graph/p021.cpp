#include <bits/stdc++.h>
using namespace std;

bool has_cycle_directed_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    vector<int> color_array(total_nodes, 0);

    function<bool(int)> dfs_detect = [&](int curr_node) -> bool {
        color_array[curr_node] = 1;
        for (int neighbor : adj_list[curr_node]) {
            if (color_array[neighbor] == 1) return true;
            if (color_array[neighbor] == 0 && dfs_detect(neighbor)) return true;
        }
        color_array[curr_node] = 2;
        return false;
    };

    for (int start_node = 0; start_node < total_nodes; start_node++) {
        if (color_array[start_node] == 0) {
            if (dfs_detect(start_node)) return true;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> adj = {{1}, {2}, {0, 3}, {4}, {5}, {}, {}, {}, {9}, {10}, {}};
    cout << (has_cycle_directed_optimal(11, adj) ? "true" : "false") << endl;
    return 0;
}
