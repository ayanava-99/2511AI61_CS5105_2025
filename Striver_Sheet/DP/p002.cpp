#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive with memoization
int minimumEnergyBrute(vector<int>& height, int n, int idx) {
    if (idx == 0) return 0;

    int oneStepBack = minimumEnergyBrute(height, n, idx - 1) + abs(height[idx] - height[idx - 1]);
    int twoStepBack = INT_MAX;
    if (idx > 1) {
        twoStepBack = minimumEnergyBrute(height, n, idx - 2) + abs(height[idx] - height[idx - 2]);
    }

    return min(oneStepBack, twoStepBack);
}

// Optimal: Tabulation approach
int minimumEnergyOptimal(vector<int>& height, int n) {
    vector<int> dp(n);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        int oneStep = dp[i - 1] + abs(height[i] - height[i - 1]);
        int twoStep = INT_MAX;
        if (i > 1) {
            twoStep = dp[i - 2] + abs(height[i] - height[i - 2]);
        }
        dp[i] = min(oneStep, twoStep);
    }

    return dp[n - 1];
}

int main() {
    int n;
    cout << "Enter number of stairs: ";
    cin >> n;

    vector<int> height(n);
    cout << "Enter heights of each stair: ";
    for (int i = 0; i < n; i++) {
        cin >> height[i];
    }

    cout << "\nBrute Force Result: " << minimumEnergyBrute(height, n, n - 1) << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << minimumEnergyOptimal(height, n) << endl;
    cout << "Time: O(n), Space: O(n)" << endl;

    return 0;
}
