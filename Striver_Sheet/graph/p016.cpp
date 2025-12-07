#include <bits/stdc++.h>
using namespace std;

void surrounded_regions_optimal(vector<vector<char>>& board_matrix) {
    int rows = board_matrix.size(), cols = board_matrix[0].size();

    function<void(int, int)> dfs_mark = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || board_matrix[r][c] != 'O') return;
        board_matrix[r][c] = '#';
        dfs_mark(r - 1, c);
        dfs_mark(r + 1, c);
        dfs_mark(r, c - 1);
        dfs_mark(r, c + 1);
    };

    for (int r = 0; r < rows; r++) {
        if (board_matrix[r][0] == 'O') dfs_mark(r, 0);
        if (board_matrix[r][cols - 1] == 'O') dfs_mark(r, cols - 1);
    }
    for (int c = 0; c < cols; c++) {
        if (board_matrix[0][c] == 'O') dfs_mark(0, c);
        if (board_matrix[rows - 1][c] == 'O') dfs_mark(rows - 1, c);
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (board_matrix[r][c] == 'O') board_matrix[r][c] = 'X';
            else if (board_matrix[r][c] == '#') board_matrix[r][c] = 'O';
        }
    }
}

int main() {
    vector<vector<char>> board = {{'X', 'X', 'X'}, {'X', 'O', 'X'}, {'X', 'X', 'X'}};
    surrounded_regions_optimal(board);
    for (auto& row : board) {
        for (char c : row) cout << c << " ";
        cout << endl;
    }
    return 0;
}
