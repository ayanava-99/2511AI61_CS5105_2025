#include <bits/stdc++.h>
using namespace std;

vector<int> articulation_points_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    vector<int> disc_time(total_nodes, -1), low_time(total_nodes, -1);
    vector<int> parent_node(total_nodes, -1);
    vector<bool> is_articulation(total_nodes, false);
    int timer_val = 0;

    function<void(int)> dfs_find_ap = [&](int u) {
        int children_count = 0;
        disc_time[u] = low_time[u] = timer_val++;

        for (int v : adj_list[u]) {
            if (disc_time[v] == -1) {
                children_count++;
                parent_node[v] = u;
                dfs_find_ap(v);
                low_time[u] = min(low_time[u], low_time[v]);

                if ((parent_node[u] == -1 && children_count > 1) || 
                    (parent_node[u] != -1 && low_time[v] >= disc_time[u])) {
                    is_articulation[u] = true;
                }
            } else if (v != parent_node[u]) {
                low_time[u] = min(low_time[u], disc_time[v]);
            }
        }
    };

    for (int node = 0; node < total_nodes; node++) {
        if (disc_time[node] == -1) {
            dfs_find_ap(node);
        }
    }

    vector<int> result_ap;
    for (int node = 0; node < total_nodes; node++) {
        if (is_articulation[node]) {
            result_ap.push_back(node);
        }
    }

    return result_ap;
}

int main() {
    vector<vector<int>> adj = {{1, 2}, {0, 2}, {0, 1, 3}, {2}};
    auto ap = articulation_points_optimal(4, adj);
    for (int node : ap) cout << node << " ";
    cout << endl;
    return 0;
}
