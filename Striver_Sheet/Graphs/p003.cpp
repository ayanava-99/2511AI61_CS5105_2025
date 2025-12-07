#include <bits/stdc++.h>
using namespace std;

// Optimal: BFS approach
int rottenOranges(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    queue<pair<pair<int, int>, int>> q;
    int freshCount = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                q.push({{i, j}, 0});
            } else if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }

    int dirs[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int time = 0;

    while (!q.empty()) {
        auto [pos, t] = q.front();
        q.pop();
        auto [row, col] = pos;
        time = max(time, t);

        for (auto& dir : dirs) {
            int nr = row + dir[0];
            int nc = col + dir[1];

            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                grid[nr][nc] = 2;
                freshCount--;
                q.push({{nr, nc}, t + 1});
            }
        }
    }

    return freshCount == 0 ? time : -1;
}

int main() {
    int m, n;
    cout << "Enter grid dimensions (m x n): ";
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));
    cout << "Enter grid (0=empty, 1=fresh, 2=rotten):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cout << "Result: " << rottenOranges(grid) << endl;
    cout << "Time: O(m*n), Space: O(m*n)" << endl;

    return 0;
}
