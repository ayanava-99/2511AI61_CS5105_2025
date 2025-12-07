#include <bits/stdc++.h>
using namespace std;

int min_effort_path_optimal(vector<vector<int>>& heights_grid) {
    int rows = heights_grid.size(), cols = heights_grid[0].size();
    vector<vector<int>> min_effort(rows, vector<int>(cols, INT_MAX));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq_effort;

    min_effort[0][0] = 0;
    pq_effort.push({0, 0, 0});

    int dirs[] = {-1, 1, 0, 0}, dirc[] = {0, 0, -1, 1};

    while (!pq_effort.empty()) {
        auto [curr_effort, r, c] = pq_effort.top();
        pq_effort.pop();

        if (curr_effort > min_effort[r][c]) continue;

        for (int d = 0; d < 4; d++) {
            int nr = r + dirs[d], nc = c + dirc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                int max_diff = max(curr_effort, abs(heights_grid[r][c] - heights_grid[nr][nc]));
                if (max_diff < min_effort[nr][nc]) {
                    min_effort[nr][nc] = max_diff;
                    pq_effort.push({max_diff, nr, nc});
                }
            }
        }
    }
    return min_effort[rows - 1][cols - 1];
}

int main() {
    vector<vector<int>> heights = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
    cout << min_effort_path_optimal(heights) << endl;
    return 0;
}
