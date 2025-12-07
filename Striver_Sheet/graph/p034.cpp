#include <bits/stdc++.h>
using namespace std;

void floyd_warshall_optimal(vector<vector<int>>& dist_matrix) {
    int n = dist_matrix.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist_matrix[i][k] != -1 && dist_matrix[k][j] != -1) {
                    if (dist_matrix[i][j] == -1) {
                        dist_matrix[i][j] = dist_matrix[i][k] + dist_matrix[k][j];
                    } else {
                        dist_matrix[i][j] = min(dist_matrix[i][j], dist_matrix[i][k] + dist_matrix[k][j]);
                    }
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> mat = {{0, 2, -1, -1}, {1, 0, 3, -1}, {-1, -1, 0, -1}, {3, 5, 4, 0}};
    floyd_warshall_optimal(mat);
    for (auto& row : mat) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    return 0;
}
