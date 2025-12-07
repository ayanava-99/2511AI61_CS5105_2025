#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
bool subsetSumBrute(vector<int>& arr, int n, int idx, int k) {
    if (k == 0) return true;
    if (idx == n || k < 0) return false;

    // Include current element
    if (subsetSumBrute(arr, n, idx + 1, k - arr[idx])) return true;

    // Exclude current element
    if (subsetSumBrute(arr, n, idx + 1, k)) return true;

    return false;
}

// Optimal: Tabulation approach
bool subsetSumOptimal(vector<int>& arr, int n, int k) {
    vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = true; // Sum of 0 is always possible
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = dp[i - 1][j]; // Don't include current element

            if (j >= arr[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i - 1]]; // Include current
            }
        }
    }

    return dp[n][k];
}

int main() {
    int n, k;
    cout << "Enter size of array: ";
    cin >> n;
    cout << "Enter target sum: ";
    cin >> k;

    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\nBrute Force Result: " << (subsetSumBrute(arr, n, 0, k) ? "YES" : "NO") << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << (subsetSumOptimal(arr, n, k) ? "YES" : "NO") << endl;
    cout << "Time: O(n*k), Space: O(n*k)" << endl;

    return 0;
}
