#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> nearest_one_distance_optimal(vector<vector<int>>& grid_binary) {
    int rows = grid_binary.size(), cols = grid_binary[0].size();
    vector<vector<int>> distance_grid(rows, vector<int>(cols, INT_MAX));
    queue<pair<int, int>> bfs_queue;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid_binary[r][c] == 1) {
                distance_grid[r][c] = 0;
                bfs_queue.push({r, c});
            }
        }
    }

    int dirs[] = {-1, 1, 0, 0}, dirc[] = {0, 0, -1, 1};

    while (!bfs_queue.empty()) {
        auto [r, c] = bfs_queue.front();
        bfs_queue.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dirs[d], nc = c + dirc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && 
                distance_grid[nr][nc] > distance_grid[r][c] + 1) {
                distance_grid[nr][nc] = distance_grid[r][c] + 1;
                bfs_queue.push({nr, nc});
            }
        }
    }
    return distance_grid;
}

int main() {
    vector<vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    auto res = nearest_one_distance_optimal(grid);
    for (auto& row : res) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    return 0;
}
