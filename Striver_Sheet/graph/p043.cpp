#include <bits/stdc++.h>
using namespace std;

int kosaraju_scc_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    stack<int> finish_stack;
    vector<bool> visited_node(total_nodes, false);

    function<void(int)> dfs_first_pass = [&](int curr_node) {
        visited_node[curr_node] = true;
        for (int neighbor : adj_list[curr_node]) {
            if (!visited_node[neighbor]) {
                dfs_first_pass(neighbor);
            }
        }
        finish_stack.push(curr_node);
    };

    for (int node = 0; node < total_nodes; node++) {
        if (!visited_node[node]) {
            dfs_first_pass(node);
        }
    }

    vector<vector<int>> rev_adj(total_nodes);
    for (int u = 0; u < total_nodes; u++) {
        for (int v : adj_list[u]) {
            rev_adj[v].push_back(u);
        }
    }

    fill(visited_node.begin(), visited_node.end(), false);
    int scc_count = 0;

    function<void(int)> dfs_second_pass = [&](int curr_node) {
        visited_node[curr_node] = true;
        for (int neighbor : rev_adj[curr_node]) {
            if (!visited_node[neighbor]) {
                dfs_second_pass(neighbor);
            }
        }
    };

    while (!finish_stack.empty()) {
        int node = finish_stack.top();
        finish_stack.pop();
        if (!visited_node[node]) {
            dfs_second_pass(node);
            scc_count++;
        }
    }

    return scc_count;
}

int main() {
    vector<vector<int>> adj = {{1}, {2}, {0, 3}, {1}};
    cout << kosaraju_scc_optimal(4, adj) << endl;
    return 0;
}
