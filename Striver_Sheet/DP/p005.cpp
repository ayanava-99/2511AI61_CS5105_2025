#include <bits/stdc++.h>
using namespace std;

int maxSumHelper(vector<int>& arr, int start, int end) {
    if (start == end) return arr[start];
    if (start > end) return 0;

    vector<int> dp(arr.size());
    dp[start] = arr[start];
    if (start + 1 <= end) dp[start + 1] = max(arr[start], arr[start + 1]);

    for (int i = start + 2; i <= end; i++) {
        dp[i] = max(arr[i] + dp[i - 2], dp[i - 1]);
    }

    return dp[end];
}

// Brute Force: Recursive approach
int maxSumBrute(vector<int>& arr, int idx, int first, int last) {
    if (idx < first || idx > last) return 0;
    if (first == last) return arr[first];

    int take = arr[idx] + maxSumBrute(arr, idx - 2, first, last);
    int skip = maxSumBrute(arr, idx - 1, first, last);

    return max(take, skip);
}

// Optimal: Handle two cases - exclude first or exclude last
int maxSumOptimal(vector<int>& arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];

    // Case 1: Exclude last element
    int case1 = maxSumHelper(arr, 0, n - 2);

    // Case 2: Exclude first element
    int case2 = maxSumHelper(arr, 1, n - 1);

    return max(case1, case2);
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements (money at each house): ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\nBrute Force Result: " << maxSumBrute(arr, n - 1, 0, n - 2) << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << maxSumOptimal(arr, n) << endl;
    cout << "Time: O(n), Space: O(n)" << endl;

    return 0;
}
