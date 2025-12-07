#include <bits/stdc++.h>
using namespace std;

// Optimal: Find all possible sums using subset sum DP
int minimumDifferenceBrute(vector<int>& arr, int n, int idx, int sum1, int sum2) {
    if (idx == n) {
        return abs(sum1 - sum2);
    }

    // Include in first subset
    int diff1 = minimumDifferenceBrute(arr, n, idx + 1, sum1 + arr[idx], sum2);

    // Include in second subset
    int diff2 = minimumDifferenceBrute(arr, n, idx + 1, sum1, sum2 + arr[idx]);

    return min(diff1, diff2);
}

// Optimal: Tabulation approach
int minimumDifferenceOptimal(vector<int>& arr, int n) {
    int totalSum = 0;
    for (int x : arr) totalSum += x;

    vector<vector<bool>> dp(n + 1, vector<bool>(totalSum + 1, false));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= totalSum; j++) {
            dp[i][j] = dp[i - 1][j];

            if (j >= arr[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    int minDiff = INT_MAX;
    for (int i = 0; i <= totalSum / 2; i++) {
        if (dp[n][i]) {
            minDiff = min(minDiff, totalSum - 2 * i);
        }
    }

    return minDiff;
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

    cout << "\nBrute Force Result: " << minimumDifferenceBrute(arr, n, 0, 0, 0) << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << minimumDifferenceOptimal(arr, n) << endl;
    cout << "Time: O(n*sum), Space: O(n*sum)" << endl;

    return 0;
}
