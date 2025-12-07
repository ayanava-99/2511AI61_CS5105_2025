#include <bits/stdc++.h>
using namespace std;

bool has_cycle_undirected_bfs_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    vector<bool> visited_node(total_nodes, false);

    for (int start_node = 0; start_node < total_nodes; start_node++) {
        if (!visited_node[start_node]) {
            queue<pair<int, int>> bfs_q;
            bfs_q.push({start_node, -1});
            visited_node[start_node] = true;

            while (!bfs_q.empty()) {
                auto [curr_node, parent_node] = bfs_q.front();
                bfs_q.pop();

                for (int neighbor : adj_list[curr_node]) {
                    if (!visited_node[neighbor]) {
                        visited_node[neighbor] = true;
                        bfs_q.push({neighbor, curr_node});
                    } else if (neighbor != parent_node) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    vector<vector<int>> adj = {{1}, {0, 2}, {1, 3}, {2}, {5}, {4, 6}, {5}};
    cout << (has_cycle_undirected_bfs_optimal(7, adj) ? 1 : 0) << endl;
    return 0;
}
