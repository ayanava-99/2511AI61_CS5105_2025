#include <bits/stdc++.h>
using namespace std;

// Brute Force: Check if subset with sum = totalSum/2 exists
bool canPartitionBrute(vector<int>& arr, int n, int idx, int sum, int target) {
    if (sum == target) return true;
    if (idx == n || sum > target) return false;

    // Include current element
    if (canPartitionBrute(arr, n, idx + 1, sum + arr[idx], target)) return true;

    // Exclude current element
    if (canPartitionBrute(arr, n, idx + 1, sum, target)) return true;

    return false;
}

// Optimal: Tabulation approach
bool canPartitionOptimal(vector<int>& arr, int n) {
    int totalSum = 0;
    for (int x : arr) totalSum += x;

    if (totalSum % 2 != 0) return false;

    int target = totalSum / 2;
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            dp[i][j] = dp[i - 1][j];

            if (j >= arr[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    return dp[n][target];
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\nBrute Force Result: " << (canPartitionBrute(arr, n, 0, 0, 0) ? "YES" : "NO") << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << (canPartitionOptimal(arr, n) ? "YES" : "NO") << endl;
    cout << "Time: O(n*sum), Space: O(n*sum)" << endl;

    return 0;
}
