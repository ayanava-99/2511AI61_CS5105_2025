#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> flood_fill_optimal(vector<vector<int>>& image_grid, int sr, int sc, int new_color_val) {
    int rows = image_grid.size(), cols = image_grid[0].size();
    int original_color = image_grid[sr][sc];

    if (original_color == new_color_val) return image_grid;

    function<void(int, int)> dfs_fill = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || image_grid[r][c] != original_color) return;
        image_grid[r][c] = new_color_val;
        dfs_fill(r - 1, c);
        dfs_fill(r + 1, c);
        dfs_fill(r, c - 1);
        dfs_fill(r, c + 1);
    };

    dfs_fill(sr, sc);
    return image_grid;
}

int main() {
    vector<vector<int>> image = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    auto res = flood_fill_optimal(image, 1, 1, 2);
    for (auto& row : res) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    return 0;
}
