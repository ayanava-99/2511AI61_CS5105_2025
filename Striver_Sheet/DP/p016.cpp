#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int countSubsetsSumBrute(vector<int>& arr, int n, int idx, int k) {
    if (k == 0) return 1;
    if (idx == n || k < 0) return 0;

    // Include current element
    int include = countSubsetsSumBrute(arr, n, idx + 1, k - arr[idx]);

    // Exclude current element
    int exclude = countSubsetsSumBrute(arr, n, idx + 1, k);

    return include + exclude;
}

// Optimal: Tabulation approach
int countSubsetsSumOptimal(vector<int>& arr, int n, int k) {
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1; // One way to make sum 0: take nothing
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = dp[i - 1][j]; // Don't include current

            if (j >= arr[i - 1]) {
                dp[i][j] += dp[i - 1][j - arr[i - 1]]; // Include current
            }
        }
    }

    return dp[n][k];
}

int main() {
    int n, k;
    cout << "Enter size of array: ";
    cin >> n;
    cout << "Enter target sum K: ";
    cin >> k;

    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\nBrute Force Result: " << countSubsetsSumBrute(arr, n, 0, k) << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << countSubsetsSumOptimal(arr, n, k) << endl;
    cout << "Time: O(n*k), Space: O(n*k)" << endl;

    return 0;
}
