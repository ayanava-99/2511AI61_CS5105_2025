#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int uniquePathsBrute(int m, int n, int x, int y) {
    if (x == m - 1 && y == n - 1) return 1;
    if (x >= m || y >= n) return 0;

    return uniquePathsBrute(m, n, x + 1, y) + uniquePathsBrute(m, n, x, y + 1);
}

// Optimal: Tabulation approach
int uniquePathsOptimal(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    return dp[m - 1][n - 1];
}

int main() {
    int m, n;
    cout << "Enter dimensions of matrix (m x n): ";
    cin >> m >> n;

    cout << "\nBrute Force Result: " << uniquePathsBrute(m, n, 0, 0) << endl;
    cout << "Time: O(2^(m+n)), Space: O(m+n)" << endl << endl;

    cout << "Optimal DP Result: " << uniquePathsOptimal(m, n) << endl;
    cout << "Time: O(m*n), Space: O(m*n)" << endl;

    return 0;
}
