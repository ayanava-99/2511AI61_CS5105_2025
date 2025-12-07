#include <bits/stdc++.h>
using namespace std;

// DFS Traversal
vector<int> dfsTraversal(int v, vector<vector<int>>& adj) {
    vector<int> result;
    vector<bool> visited(v, false);

    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        result.push_back(node);

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    };

    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    return result;
}

int main() {
    int v, e;
    cout << "Enter V and E: ";
    cin >> v >> e;

    vector<vector<int>> adj(v);
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> result = dfsTraversal(v, adj);
    cout << "DFS: ";
    for (int node : result) cout << node << " ";
    cout << "\nTime: O(V+E), Space: O(V)" << endl;

    return 0;
}
