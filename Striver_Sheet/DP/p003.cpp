#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int minimumEnergyBrute(vector<int>& height, int n, int idx, int k) {
    if (idx == 0) return 0;

    int minEnergy = INT_MAX;

    for (int i = 1; i <= k && i <= idx; i++) {
        int energy = minimumEnergyBrute(height, n, idx - i, k) + abs(height[idx] - height[idx - i]);
        minEnergy = min(minEnergy, energy);
    }

    return minEnergy;
}

// Optimal: Tabulation with space optimization
int minimumEnergyOptimal(vector<int>& height, int n, int k) {
    vector<int> dp(n);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        int minEnergy = INT_MAX;

        for (int j = 1; j <= k && j <= i; j++) {
            int energy = dp[i - j] + abs(height[i] - height[i - j]);
            minEnergy = min(minEnergy, energy);
        }

        dp[i] = minEnergy;
    }

    return dp[n - 1];
}

int main() {
    int n, k;
    cout << "Enter number of stairs: ";
    cin >> n;
    cout << "Enter maximum steps allowed: ";
    cin >> k;

    vector<int> height(n);
    cout << "Enter heights of each stair: ";
    for (int i = 0; i < n; i++) {
        cin >> height[i];
    }

    cout << "\nBrute Force Result: " << minimumEnergyBrute(height, n, n - 1, k) << endl;
    cout << "Time: O(k^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << minimumEnergyOptimal(height, n, k) << endl;
    cout << "Time: O(n*k), Space: O(n)" << endl;

    return 0;
}
