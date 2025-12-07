#include <bits/stdc++.h>
using namespace std;

// Brute Force: Recursive approach
bool wildcardMatchBrute(const string& s, const string& p, int sIdx, int pIdx) {
    if (pIdx == p.length()) {
        return sIdx == s.length();
    }

    if (p[pIdx] == '*') {
        // Match zero characters
        if (wildcardMatchBrute(s, p, sIdx, pIdx + 1)) return true;

        // Match one or more characters
        if (sIdx < s.length() && wildcardMatchBrute(s, p, sIdx + 1, pIdx)) return true;

        return false;
    }

    if (sIdx == s.length()) return false;

    if (p[pIdx] == '?' || p[pIdx] == s[sIdx]) {
        return wildcardMatchBrute(s, p, sIdx + 1, pIdx + 1);
    }

    return false;
}

// Optimal: Tabulation approach
bool wildcardMatchOptimal(const string& s, const string& p) {
    int sLen = s.length();
    int pLen = p.length();

    vector<vector<bool>> dp(sLen + 1, vector<bool>(pLen + 1, false));

    dp[0][0] = true;

    // Handle patterns like *, **, etc.
    for (int j = 1; j <= pLen; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 1];
        }
    }

    for (int i = 1; i <= sLen; i++) {
        for (int j = 1; j <= pLen; j++) {
            if (p[j - 1] == '*') {
                // Match zero or more characters
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                // Match single character
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }

    return dp[sLen][pLen];
}

int main() {
    string s, p;
    cout << "Enter string S: ";
    cin >> s;
    cout << "Enter pattern P (? and * allowed): ";
    cin >> p;

    cout << "\nBrute Force Result: " << (wildcardMatchBrute(s, p, 0, 0) ? "MATCH" : "NO MATCH") << endl;
    cout << "Time: O(2^(s+p)), Space: O(s+p)" << endl << endl;

    cout << "Optimal DP Result: " << (wildcardMatchOptimal(s, p) ? "MATCH" : "NO MATCH") << endl;
    cout << "Time: O(s*p), Space: O(s*p)" << endl;

    return 0;
}
