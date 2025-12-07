#include <bits/stdc++.h>
using namespace std;

vector<int> topological_sort_dfs_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    vector<bool> visited_node(total_nodes, false);
    stack<int> topo_stack;

    function<void(int)> dfs_topo = [&](int curr_node) {
        visited_node[curr_node] = true;
        for (int neighbor : adj_list[curr_node]) {
            if (!visited_node[neighbor]) {
                dfs_topo(neighbor);
            }
        }
        topo_stack.push(curr_node);
    };

    for (int start_node = 0; start_node < total_nodes; start_node++) {
        if (!visited_node[start_node]) {
            dfs_topo(start_node);
        }
    }

    vector<int> result_topo;
    while (!topo_stack.empty()) {
        result_topo.push_back(topo_stack.top());
        topo_stack.pop();
    }
    return result_topo;
}

int main() {
    int nodes = 6;
    vector<vector<int>> adj = {{}, {}, {3}, {1}, {0, 1}, {0, 2}};
    auto res = topological_sort_dfs_optimal(nodes, adj);
    for (int v : res) cout << v << " ";
    cout << endl;
    return 0;
}
