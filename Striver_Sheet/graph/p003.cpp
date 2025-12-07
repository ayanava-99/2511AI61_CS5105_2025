#include <bits/stdc++.h>
using namespace std;

int rotten_oranges_optimal(vector<vector<int>>& grid_matrix) {
    int rows = grid_matrix.size(), cols = grid_matrix[0].size();
    queue<pair<int, int>> rotten_queue;
    int fresh_count = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid_matrix[r][c] == 2) rotten_queue.push({r, c});
            else if (grid_matrix[r][c] == 1) fresh_count++;
        }
    }

    if (fresh_count == 0) return 0;

    int direction_rows[] = {-1, 1, 0, 0};
    int direction_cols[] = {0, 0, -1, 1};
    int time_elapsed = 0;

    while (!rotten_queue.empty() && fresh_count > 0) {
        int queue_size = rotten_queue.size();
        for (int i = 0; i < queue_size; i++) {
            auto [curr_r, curr_c] = rotten_queue.front();
            rotten_queue.pop();

            for (int d = 0; d < 4; d++) {
                int next_r = curr_r + direction_rows[d];
                int next_c = curr_c + direction_cols[d];

                if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols && 
                    grid_matrix[next_r][next_c] == 1) {
                    grid_matrix[next_r][next_c] = 2;
                    fresh_count--;
                    rotten_queue.push({next_r, next_c});
                }
            }
        }
        if (fresh_count > 0) time_elapsed++;
    }

    return fresh_count == 0 ? time_elapsed : -1;
}

int main() {
    vector<vector<int>> grid1 = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    cout << rotten_oranges_optimal(grid1) << endl;
    return 0;
}
