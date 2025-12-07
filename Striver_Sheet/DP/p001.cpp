#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach - exponential time
int countWaysBrute(int n) {
    // Base cases
    if (n == 0 || n == 1) return 1;

    // At each stair, we can come from (n-1) or (n-2)
    return countWaysBrute(n - 1) + countWaysBrute(n - 2);
}

// Optimal: Dynamic Programming - Tabulation
int countWaysOptimal(int n) {
    if (n == 0 || n == 1) return 1;

    vector<int> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int main() {
    int n;
    cout << "Enter number of stairs: ";
    cin >> n;

    cout << "Brute Force Result: " << countWaysBrute(n) << endl;
    cout << "Time: O(2^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << countWaysOptimal(n) << endl;
    cout << "Time: O(n), Space: O(n)" << endl;

    return 0;
}
