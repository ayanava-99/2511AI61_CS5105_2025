#include <bits/stdc++.h>
using namespace std;

int find_city_threshold_optimal(int total_cities, vector<vector<int>>& edges_list, int distance_threshold) {
    vector<vector<int>> dist_mat(total_cities, vector<int>(total_cities, INT_MAX));

    for (int i = 0; i < total_cities; i++) dist_mat[i][i] = 0;

    for (auto& edge : edges_list) {
        dist_mat[edge[0]][edge[1]] = min(dist_mat[edge[0]][edge[1]], edge[2]);
        dist_mat[edge[1]][edge[0]] = min(dist_mat[edge[1]][edge[0]], edge[2]);
    }

    for (int k = 0; k < total_cities; k++) {
        for (int i = 0; i < total_cities; i++) {
            for (int j = 0; j < total_cities; j++) {
                if (dist_mat[i][k] != INT_MAX && dist_mat[k][j] != INT_MAX) {
                    dist_mat[i][j] = min(dist_mat[i][j], dist_mat[i][k] + dist_mat[k][j]);
                }
            }
        }
    }

    int min_reachable = INT_MAX, result_city = -1;
    for (int city = 0; city < total_cities; city++) {
        int reachable_count = 0;
        for (int other = 0; other < total_cities; other++) {
            if (dist_mat[city][other] <= distance_threshold) reachable_count++;
        }
        if (reachable_count < min_reachable) {
            min_reachable = reachable_count;
            result_city = city;
        }
    }

    return result_city;
}

int main() {
    vector<vector<int>> edges = {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};
    cout << find_city_threshold_optimal(4, edges, 4) << endl;
    return 0;
}
