#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int minPathSumBrute(vector<vector<int>>& matrix, int m, int n, int x, int y) {
    if (x >= m || y >= n) return INT_MAX;
    if (x == m - 1 && y == n - 1) return matrix[x][y];

    int right = minPathSumBrute(matrix, m, n, x, y + 1);
    int down = minPathSumBrute(matrix, m, n, x + 1, y);

    return matrix[x][y] + min(right, down);
}

// Optimal: Tabulation approach
int minPathSumOptimal(vector<vector<int>>& matrix, int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n));

    dp[0][0] = matrix[0][0];

    // Fill first row
    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j - 1] + matrix[0][j];
    }

    // Fill first column
    for (int i = 1; i < m; i++) {
        dp[i][0] = dp[i - 1][0] + matrix[i][0];
    }

    // Fill rest
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = matrix[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[m - 1][n - 1];
}

int main() {
    int m, n;
    cout << "Enter dimensions of matrix (m x n): ";
    cin >> m >> n;

    vector<vector<int>> matrix(m, vector<int>(n));
    cout << "Enter matrix elements:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    cout << "\nBrute Force Result: " << minPathSumBrute(matrix, m, n, 0, 0) << endl;
    cout << "Time: O(2^(m+n)), Space: O(m+n)" << endl << endl;

    cout << "Optimal DP Result: " << minPathSumOptimal(matrix, m, n) << endl;
    cout << "Time: O(m*n), Space: O(m*n)" << endl;

    return 0;
}
