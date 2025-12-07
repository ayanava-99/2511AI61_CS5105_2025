#include <bits/stdc++.h>
using namespace std;

// Optimal: Multi-source BFS
vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<int>> dist(m, vector<int>(n, -1));
    queue<pair<int, int>> q;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    int dirs[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();

        for (auto& dir : dirs) {
            int nr = row + dir[0];
            int nc = col + dir[1];

            if (nr >= 0 && nr < m && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[row][col] + 1;
                q.push({nr, nc});
            }
        }
    }

    return dist;
}

int main() {
    int m, n;
    cout << "Enter grid dimensions (m x n): ";
    cin >> m >> n;

    vector<vector<int>> mat(m, vector<int>(n));
    cout << "Enter grid (0 or 1):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    vector<vector<int>> result = updateMatrix(mat);
    cout << "Result:\n";
    for (auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "Time: O(m*n), Space: O(m*n)" << endl;

    return 0;
}
