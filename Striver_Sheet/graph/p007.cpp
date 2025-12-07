#include <bits/stdc++.h>
using namespace std;

int shortest_maze_bfs_optimal(vector<vector<int>>& grid_maze, vector<int>& src_pos, vector<int>& dst_pos) {
    int rows = grid_maze.size(), cols = grid_maze[0].size();
    if (grid_maze[src_pos[0]][src_pos[1]] == 0 || grid_maze[dst_pos[0]][dst_pos[1]] == 0) return -1;

    vector<vector<int>> dist_grid(rows, vector<int>(cols, -1));
    queue<pair<int, int>> bfs_q;

    dist_grid[src_pos[0]][src_pos[1]] = 0;
    bfs_q.push({src_pos[0], src_pos[1]});

    int dirs[] = {-1, 1, 0, 0}, dirc[] = {0, 0, -1, 1};

    while (!bfs_q.empty()) {
        auto [r, c] = bfs_q.front();
        bfs_q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dirs[d], nc = c + dirc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && 
                grid_maze[nr][nc] == 1 && dist_grid[nr][nc] == -1) {
                dist_grid[nr][nc] = dist_grid[r][c] + 1;
                bfs_q.push({nr, nc});
            }
        }
    }
    return dist_grid[dst_pos[0]][dst_pos[1]];
}

int main() {
    vector<vector<int>> grid = {{1, 1, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 1}, {1, 1, 0, 0}, {1, 0, 0, 1}};
    vector<int> src = {0, 1}, dst = {2, 2};
    cout << shortest_maze_bfs_optimal(grid, src, dst) << endl;
    return 0;
}
