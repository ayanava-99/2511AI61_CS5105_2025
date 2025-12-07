#include <bits/stdc++.h>
using namespace std;

// Approach: Use subset sum to find count of subsets with sum S1 where
// S1 - S2 = diff and S1 + S2 = totalSum
// Solving: S1 = (totalSum + diff) / 2

// Optimal: Tabulation approach
int countPartitionsOptimal(vector<int>& arr, int n, int diff) {
    int totalSum = 0;
    for (int x : arr) totalSum += x;

    // S1 - S2 = diff and S1 + S2 = totalSum
    // Therefore: 2*S1 = totalSum + diff
    if ((totalSum + diff) % 2 != 0 || totalSum + diff < 0) return 0;

    int target = (totalSum + diff) / 2;
    if (target < 0) return 0;

    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            dp[i][j] = dp[i - 1][j]; // Don't include

            if (j >= arr[i - 1]) {
                dp[i][j] += dp[i - 1][j - arr[i - 1]]; // Include
            }
        }
    }

    return dp[n][target];
}

int main() {
    int n, diff;
    cout << "Enter size of array: ";
    cin >> n;
    cout << "Enter required difference: ";
    cin >> diff;

    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\nOptimal DP Result: " << countPartitionsOptimal(arr, n, diff) << endl;
    cout << "Time: O(n*target), Space: O(n*target)" << endl;

    return 0;
}
