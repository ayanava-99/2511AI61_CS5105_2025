#include <bits/stdc++.h>
using namespace std;

// Optimal: Tabulation with 3D DP
// Think of it as two people moving simultaneously from (0,0) to (m-1, n-1)
int cherryPickupOptimal(vector<vector<int>>& mat, int m, int n) {
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, -1)));

    function<int(int, int, int)> solve = [&](int r, int c1, int c2) -> int {
        int c2_calc = r - c1 + c2; // Calculate c2 based on r and c1

        if (c1 >= n || c2_calc >= n || c1 < 0 || c2_calc < 0) return INT_MIN / 2;
        if (r == m - 1) {
            if (c1 == c2_calc) return mat[r][c1];
            return INT_MIN / 2;
        }

        if (dp[r][c1][c2_calc] != -1) return dp[r][c1][c2_calc];

        int result = 0;
        if (c1 == c2_calc) result = mat[r][c1];
        else result = mat[r][c1] + mat[r][c2_calc];

        int maxNext = INT_MIN / 2;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                maxNext = max(maxNext, solve(r + 1, c1 + i, c2 + j));
            }
        }

        return dp[r][c1][c2_calc] = result + maxNext;
    };

    return max(0, solve(0, 0, 0));
}

int main() {
    int m, n;
    cout << "Enter dimensions of matrix (m x n): ";
    cin >> m >> n;

    vector<vector<int>> mat(m, vector<int>(n));
    cout << "Enter matrix elements (chocolates at each cell):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    cout << "\nOptimal DP Result: " << cherryPickupOptimal(mat, m, n) << endl;
    cout << "Time: O(m*n^2), Space: O(m*n^2)" << endl;

    return 0;
}
