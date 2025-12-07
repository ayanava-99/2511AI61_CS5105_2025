#include <bits/stdc++.h>
using namespace std;

// Brute Force: DFS-based approach (not optimal for BFS but showing for comparison)
vector<int> bfsBrute(int v, vector<vector<int>>& adj) {
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
        if (!visited[i]) dfs(i);
    }
    return result;
}

// Optimal: BFS using Queue
vector<int> bfsOptimal(int v, vector<vector<int>>& adj) {
    vector<int> result;
    vector<bool> visited(v, false);
    queue<int> q;

    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                result.push_back(node);

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
    return result;
}

int main() {
    int v, e;
    cout << "Enter number of vertices and edges: ";
    cin >> v >> e;

    vector<vector<int>> adj(v);
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "\nBrute Force (DFS): ";
    vector<int> bruteRes = bfsBrute(v, adj);
    for (int node : bruteRes) cout << node << " ";
    cout << "\nTime: O(V+E), Space: O(V)" << endl << endl;

    cout << "Optimal (BFS): ";
    vector<int> optRes = bfsOptimal(v, adj);
    for (int node : optRes) cout << node << " ";
    cout << "\nTime: O(V+E), Space: O(V)" << endl;

    return 0;
}
