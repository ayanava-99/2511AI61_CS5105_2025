#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int targetSumBrute(vector<int>& arr, int n, int idx, int currentSum, int target) {
    if (idx == n) {
        return currentSum == target ? 1 : 0;
    }

    // Add current element
    int add = targetSumBrute(arr, n, idx + 1, currentSum + arr[idx], target);

    // Subtract current element
    int subtract = targetSumBrute(arr, n, idx + 1, currentSum - arr[idx], target);

    return add + subtract;
}

// Optimal: Convert to subset sum problem
// If we assign +S1 to some elements and -S2 to others:
// S1 - S2 = target and S1 + S2 = totalSum
// Therefore: S1 = (totalSum + target) / 2
int targetSumOptimal(vector<int>& arr, int n, int target) {
    int totalSum = 0;
    for (int x : arr) totalSum += x;

    if ((totalSum + target) % 2 != 0 || abs(target) > totalSum) return 0;

    int sum = (totalSum + target) / 2;
    if (sum < 0) return 0;

    vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            dp[i][j] = dp[i - 1][j];

            if (j >= arr[i - 1]) {
                dp[i][j] += dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    return dp[n][sum];
}

int main() {
    int n, target;
    cout << "Enter size of array: ";
    cin >> n;
    cout << "Enter target sum: ";
    cin >> target;

    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\nBrute Force Result: " << targetSumBrute(arr, n, 0, 0, target) << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << targetSumOptimal(arr, n, target) << endl;
    cout << "Time: O(n*sum), Space: O(n*sum)" << endl;

    return 0;
}
