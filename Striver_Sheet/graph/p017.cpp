#include <bits/stdc++.h>
using namespace std;

int count_enclaves_optimal(vector<vector<int>>& grid_enclave) {
    int rows = grid_enclave.size(), cols = grid_enclave[0].size();

    function<void(int, int)> dfs_mark_boundary = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid_enclave[r][c] == 0) return;
        grid_enclave[r][c] = 0;
        dfs_mark_boundary(r - 1, c);
        dfs_mark_boundary(r + 1, c);
        dfs_mark_boundary(r, c - 1);
        dfs_mark_boundary(r, c + 1);
    };

    for (int r = 0; r < rows; r++) {
        if (grid_enclave[r][0] == 1) dfs_mark_boundary(r, 0);
        if (grid_enclave[r][cols - 1] == 1) dfs_mark_boundary(r, cols - 1);
    }
    for (int c = 0; c < cols; c++) {
        if (grid_enclave[0][c] == 1) dfs_mark_boundary(0, c);
        if (grid_enclave[rows - 1][c] == 1) dfs_mark_boundary(rows - 1, c);
    }

    int enclave_count = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid_enclave[r][c] == 1) enclave_count++;
        }
    }
    return enclave_count;
}

int main() {
    vector<vector<int>> grid = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    cout << count_enclaves_optimal(grid) << endl;
    return 0;
}
