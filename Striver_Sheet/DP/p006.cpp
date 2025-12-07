#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
int maxPointsBrute(vector<vector<int>>& points, int day, int lastActivity) {
    if (day == 0) {
        int maxPoints = 0;
        for (int i = 0; i < 3; i++) {
            if (i != lastActivity) {
                maxPoints = max(maxPoints, points[0][i]);
            }
        }
        return maxPoints;
    }

    int maxPoints = 0;
    for (int i = 0; i < 3; i++) {
        if (i != lastActivity) {
            maxPoints = max(maxPoints, points[day][i] + maxPointsBrute(points, day - 1, i));
        }
    }

    return maxPoints;
}

// Optimal: Tabulation approach
int maxPointsOptimal(vector<vector<int>>& points, int n) {
    vector<vector<int>> dp(n, vector<int>(3));

    // Day 0: Choose any activity
    dp[0][0] = points[0][0];
    dp[0][1] = points[0][1];
    dp[0][2] = points[0][2];

    for (int day = 1; day < n; day++) {
        for (int lastActivity = 0; lastActivity < 3; lastActivity++) {
            dp[day][lastActivity] = points[day][lastActivity];
            int maxPrev = 0;
            for (int i = 0; i < 3; i++) {
                if (i != lastActivity) {
                    maxPrev = max(maxPrev, dp[day - 1][i]);
                }
            }
            dp[day][lastActivity] += maxPrev;
        }
    }

    return max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
}

int main() {
    int n;
    cout << "Enter number of days: ";
    cin >> n;

    vector<vector<int>> points(n, vector<int>(3));
    cout << "Enter merit points for each activity (Running, Fighting, Learning) for each day:\n";
    for (int i = 0; i < n; i++) {
        cout << "Day " << i << ": ";
        for (int j = 0; j < 3; j++) {
            cin >> points[i][j];
        }
    }

    cout << "\nBrute Force Result: " << maxPointsBrute(points, n - 1, -1) << endl;
    cout << "Time: O(3^n), Space: O(n)" << endl << endl;

    cout << "Optimal DP Result: " << maxPointsOptimal(points, n) << endl;
    cout << "Time: O(n), Space: O(n)" << endl;

    return 0;
}
