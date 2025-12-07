#include <bits/stdc++.h>
using namespace std;

vector<int> dfs_traversal_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    vector<int> result_dfs;
    vector<bool> visited_dfs(total_nodes, false);

    function<void(int)> dfs_recursive = [&](int curr_node) {
        visited_dfs[curr_node] = true;
        result_dfs.push_back(curr_node);
        for (int neighbor : adj_list[curr_node]) {
            if (!visited_dfs[neighbor]) {
                dfs_recursive(neighbor);
            }
        }
    };

    dfs_recursive(0);
    return result_dfs;
}

int main() {
    int nodes = 5;
    vector<vector<int>> adj = {{1, 2}, {0, 3}, {0, 4}, {1}, {1}};
    auto res = dfs_traversal_optimal(nodes, adj);
    for (int v : res) cout << v << " ";
    cout << endl;
    return 0;
}
