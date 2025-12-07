#include <bits/stdc++.h>
using namespace std;

vector<int> bfs_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    vector<int> result_bfs;
    vector<bool> visited_bfs(total_nodes, false);
    queue<int> q_bfs;

    q_bfs.push(0);
    visited_bfs[0] = true;

    while (!q_bfs.empty()) {
        int curr_node = q_bfs.front();
        q_bfs.pop();
        result_bfs.push_back(curr_node);

        for (int neighbor : adj_list[curr_node]) {
            if (!visited_bfs[neighbor]) {
                visited_bfs[neighbor] = true;
                q_bfs.push(neighbor);
            }
        }
    }
    return result_bfs;
}

int main() {
    int total_nodes = 5;
    vector<vector<int>> adj_list = {{1, 2}, {0, 3}, {0, 4}, {1}, {1}};

    vector<int> res = bfs_optimal(total_nodes, adj_list);
    for (int val : res) cout << val << " ";
    cout << endl;
    return 0;
}
