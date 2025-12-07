#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int uniquePathsBrute(vector<vector<int>>& maze, int m, int n, int x, int y) {
    if (x >= m || y >= n || maze[x][y] == -1) return 0;
    if (x == m - 1 && y == n - 1) return 1;

    return uniquePathsBrute(maze, m, n, x + 1, y) + uniquePathsBrute(maze, m, n, x, y + 1);
}

// Optimal: Tabulation approach
int uniquePathsOptimal(vector<vector<int>>& maze, int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));

    dp[0][0] = (maze[0][0] == -1) ? 0 : 1;

    // Fill first row
    for (int j = 1; j < n; j++) {
        if (maze[0][j] == -1) dp[0][j] = 0;
        else dp[0][j] = dp[0][j - 1];
    }

    // Fill first column
    for (int i = 1; i < m; i++) {
        if (maze[i][0] == -1) dp[i][0] = 0;
        else dp[i][0] = dp[i - 1][0];
    }

    // Fill rest
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (maze[i][j] == -1) dp[i][j] = 0;
            else dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    return dp[m - 1][n - 1];
}

int main() {
    int m, n;
    cout << "Enter dimensions of maze (m x n): ";
    cin >> m >> n;

    vector<vector<int>> maze(m, vector<int>(n));
    cout << "Enter maze (-1 for blockage, 0 for non-blockage):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> maze[i][j];
        }
    }

    cout << "\nBrute Force Result: " << uniquePathsBrute(maze, m, n, 0, 0) << endl;
    cout << "Time: O(2^(m+n)), Space: O(m+n)" << endl << endl;

    cout << "Optimal DP Result: " << uniquePathsOptimal(maze, m, n) << endl;
    cout << "Time: O(m*n), Space: O(m*n)" << endl;

    return 0;
}
