#include <bits/stdc++.h>
using namespace std;

// Brute Force: Using recursion without optimization
int provincesBrute(int city, vector<vector<int>>& isConnected, vector<bool>& visited) {
    visited[city] = true;
    for (int i = 0; i < isConnected.size(); i++) {
        if (isConnected[city][i] && !visited[i]) {
            provincesBrute(i, isConnected, visited);
        }
    }
    return 1;
}

// Optimal: DFS with early termination
int provincesOptimal(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<bool> visited(n, false);
    int provinces = 0;

    function<void(int)> dfs = [&](int city) {
        visited[city] = true;
        for (int i = 0; i < n; i++) {
            if (isConnected[city][i] && !visited[i]) {
                dfs(i);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            provinces++;
        }
    }
    return provinces;
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> isConnected(n, vector<int>(n));
    cout << "Enter adjacency matrix (1 if connected, 0 otherwise):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> isConnected[i][j];
        }
    }

    cout << "\nBrute Force Result: ";
    vector<bool> visited(n, false);
    int bruteRes = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            provincesBrute(i, isConnected, visited);
            bruteRes++;
        }
    }
    cout << bruteRes << "\nTime: O(V^2), Space: O(V)" << endl << endl;

    cout << "Optimal Result: " << provincesOptimal(isConnected) << endl;
    cout << "Time: O(V^2), Space: O(V)" << endl;

    return 0;
}
