#include <bits/stdc++.h>
using namespace std;

// Optimal: BFS coloring approach
int isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : graph[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n);
    cout << "Enter adjacency list (end each list with -1):\n";
    for (int i = 0; i < n; i++) {
        int node;
        while (cin >> node && node != -1) {
            graph[i].push_back(node);
        }
    }

    cout << "Result: " << isBipartite(graph) << endl;
    cout << "Time: O(V+E), Space: O(V)" << endl;

    return 0;
}
