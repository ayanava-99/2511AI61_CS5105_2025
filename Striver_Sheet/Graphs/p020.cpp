#include <bits/stdc++.h>
using namespace std;

// Number of Islands - DFS
int numIslands(vector<vector<char>>& grid) {
    if (grid.empty()) return 0;

    int m = grid.size(), n = grid[0].size();
    int count = 0;

    function<void(int, int)> dfs = [&](int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1') return;
        grid[i][j] = '0';

        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (abs(di) + abs(dj) <= 1) {
                    dfs(i + di, j + dj);
                }
            }
        }
    };

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1') {
                dfs(i, j);
                count++;
            }
        }
    }

    return count;
}

int main() {
    int m, n;
    cout << "Enter grid dimensions: ";
    cin >> m >> n;

    vector<vector<char>> grid(m, vector<char>(n));
    cout << "Enter grid (0=water, 1=land):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cout << "Number of Islands: " << numIslands(grid) << endl;
    cout << "Time: O(m*n), Space: O(m*n)" << endl;

    return 0;
}
