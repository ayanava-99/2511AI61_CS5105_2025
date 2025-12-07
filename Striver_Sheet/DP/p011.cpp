#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int maxPathBrute(vector<vector<int>>& matrix, int m, int n, int row, int col) {
    if (col < 0 || col >= n) return INT_MIN;
    if (row == m - 1) return matrix[row][col];

    int down = maxPathBrute(matrix, m, n, row + 1, col);
    int diagLeft = maxPathBrute(matrix, m, n, row + 1, col - 1);
    int diagRight = maxPathBrute(matrix, m, n, row + 1, col + 1);

    return matrix[row][col] + max({down, diagLeft, diagRight});
}

// Optimal: Tabulation approach
int maxPathOptimal(vector<vector<int>>& matrix, int m, int n) {
    vector<vector<int>> dp = matrix;

    for (int i = m - 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            int down = dp[i + 1][j];
            int diagLeft = (j > 0) ? dp[i + 1][j - 1] : INT_MIN;
            int diagRight = (j < n - 1) ? dp[i + 1][j + 1] : INT_MIN;

            dp[i][j] += max({down, diagLeft, diagRight});
        }
    }

    int maxSum = INT_MIN;
    for (int j = 0; j < n; j++) {
        maxSum = max(maxSum, dp[0][j]);
    }

    return maxSum;
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

    int maxSum = INT_MIN;
    for (int j = 0; j < n; j++) {
        maxSum = max(maxSum, maxPathBrute(matrix, m, n, 0, j));
    }
    cout << "\nBrute Force Result: " << maxSum << endl;
    cout << "Time: O(3^m), Space: O(m)" << endl << endl;

    cout << "Optimal DP Result: " << maxPathOptimal(matrix, m, n) << endl;
    cout << "Time: O(m*n), Space: O(m*n)" << endl;

    return 0;
}
