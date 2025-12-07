#include <bits/stdc++.h>
using namespace std;

int count_islands_optimal(vector<vector<char>>& grid_islands) {
    int rows = grid_islands.size(), cols = grid_islands[0].size();
    int island_count = 0;

    function<void(int, int)> dfs_explore = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid_islands[r][c] != '1') return;
        grid_islands[r][c] = '0';
        dfs_explore(r - 1, c);
        dfs_explore(r + 1, c);
        dfs_explore(r, c - 1);
        dfs_explore(r, c + 1);
        dfs_explore(r - 1, c - 1);
        dfs_explore(r - 1, c + 1);
        dfs_explore(r + 1, c - 1);
        dfs_explore(r + 1, c + 1);
    };

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid_islands[r][c] == '1') {
                island_count++;
                dfs_explore(r, c);
            }
        }
    }
    return island_count;
}

int main() {
    vector<vector<char>> grid = {{'1', '1', '0'}, {'0', '1', '0'}, {'1', '0', '1'}};
    cout << count_islands_optimal(grid) << endl;
    return 0;
}
