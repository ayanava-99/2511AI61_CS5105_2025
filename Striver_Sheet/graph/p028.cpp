#include <bits/stdc++.h>
using namespace std;

vector<int> shortest_path_unit_bfs_optimal(int total_nodes, vector<vector<int>>& edges_list) {
    vector<vector<int>> adj_list(total_nodes);
    for (auto& edge : edges_list) {
        adj_list[edge[0]].push_back(edge[1]);
        adj_list[edge[1]].push_back(edge[0]);
    }

    vector<int> distance_arr(total_nodes, -1);
    queue<int> bfs_q;

    bfs_q.push(0);
    distance_arr[0] = 0;

    while (!bfs_q.empty()) {
        int curr_node = bfs_q.front();
        bfs_q.pop();

        for (int neighbor : adj_list[curr_node]) {
            if (distance_arr[neighbor] == -1) {
                distance_arr[neighbor] = distance_arr[curr_node] + 1;
                bfs_q.push(neighbor);
            }
        }
    }

    return distance_arr;
}

int main() {
    vector<vector<int>> edges = {{0, 1}, {0, 3}, {3, 4}, {4, 5}, {5, 6}, {1, 2}, {2, 6}, {6, 7}, {7, 8}, {6, 8}};
    auto dist = shortest_path_unit_bfs_optimal(9, edges);
    for (int d : dist) cout << d << " ";
    cout << endl;
    return 0;
}
