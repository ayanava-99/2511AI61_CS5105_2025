#include <bits/stdc++.h>
using namespace std;

vector<int> safe_nodes_optimal(int total_nodes, vector<vector<int>>& adj_list) {
    vector<vector<int>> rev_adj(total_nodes);
    vector<int> out_degree(total_nodes);

    for (int u = 0; u < total_nodes; u++) {
        for (int v : adj_list[u]) {
            rev_adj[v].push_back(u);
            out_degree[u]++;
        }
    }

    queue<int> q;
    for (int node = 0; node < total_nodes; node++) {
        if (out_degree[node] == 0) q.push(node);
    }

    set<int> safe_set;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        safe_set.insert(curr);

        for (int prev : rev_adj[curr]) {
            out_degree[prev]--;
            if (out_degree[prev] == 0) q.push(prev);
        }
    }

    return vector<int>(safe_set.begin(), safe_set.end());
}

int main() {
    vector<vector<int>> adj = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    auto safe = safe_nodes_optimal(7, adj);
    for (int s : safe) cout << s << " ";
    cout << endl;
    return 0;
}
