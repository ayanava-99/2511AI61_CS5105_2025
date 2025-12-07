#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int minPathBrute(vector<vector<int>>& triangle, int row, int col) {
    if (row == triangle.size() - 1) return triangle[row][col];

    int down = minPathBrute(triangle, row + 1, col);
    int diag = minPathBrute(triangle, row + 1, col + 1);

    return triangle[row][col] + min(down, diag);
}

// Optimal: Tabulation approach (bottom-up)
int minPathOptimal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> dp = triangle[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
        }
    }

    return dp[0];
}

int main() {
    int n;
    cout << "Enter number of rows in triangle: ";
    cin >> n;

    vector<vector<int>> triangle(n);
    cout << "Enter triangle elements (row by row):\n";
    for (int i = 0; i < n; i++) {
        triangle[i].resize(i + 1);
        for (int j = 0; j <= i; j++) {
            cin >> triangle[i][j];
        }
    }

    cout << "\nBrute Force Result: " << minPathBrute(triangle, 0, 0) << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << minPathOptimal(triangle) << endl;
    cout << "Time: O(n^2), Space: O(n)" << endl;

    return 0;
}
