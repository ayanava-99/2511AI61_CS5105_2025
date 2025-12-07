#include <bits/stdc++.h>
using namespace std;

vector<int> kahn_topological_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    vector<int> indegree_array(total_nodes, 0);
    for (int node = 0; node < total_nodes; node++) {
        for (int neighbor : adj_list[node]) {
            indegree_array[neighbor]++;
        }
    }

    queue<int> kahn_queue;
    for (int node = 0; node < total_nodes; node++) {
        if (indegree_array[node] == 0) {
            kahn_queue.push(node);
        }
    }

    vector<int> topo_result;
    while (!kahn_queue.empty()) {
        int curr_node = kahn_queue.front();
        kahn_queue.pop();
        topo_result.push_back(curr_node);

        for (int neighbor : adj_list[curr_node]) {
            indegree_array[neighbor]--;
            if (indegree_array[neighbor] == 0) {
                kahn_queue.push(neighbor);
            }
        }
    }
    return topo_result;
}

int main() {
    int nodes = 6;
    vector<vector<int>> adj = {{}, {}, {3}, {1}, {0, 1}, {0, 2}};
    auto res = kahn_topological_optimal(nodes, adj);
    for (int v : res) cout << v << " ";
    cout << endl;
    return 0;
}
