#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int maxSumBrute(vector<int>& arr, int idx) {
    if (idx < 0) return 0;
    if (idx == 0) return arr[0];

    int take = arr[idx] + maxSumBrute(arr, idx - 2);
    int skip = maxSumBrute(arr, idx - 1);

    return max(take, skip);
}

// Optimal: Tabulation approach
int maxSumOptimal(vector<int>& arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];

    vector<int> dp(n);
    dp[0] = arr[0];
    dp[1] = max(arr[0], arr[1]);

    for (int i = 2; i < n; i++) {
        dp[i] = max(arr[i] + dp[i - 2], dp[i - 1]);
    }

    return dp[n - 1];
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

    cout << "\nBrute Force Result: " << maxSumBrute(arr, n - 1) << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << maxSumOptimal(arr, n) << endl;
    cout << "Time: O(n), Space: O(n)" << endl;

    return 0;
}
