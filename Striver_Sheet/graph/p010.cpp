#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent_arr, rank_arr;
    DSU(int n) : parent_arr(n), rank_arr(n, 0) {
        iota(parent_arr.begin(), parent_arr.end(), 0);
    }
    int find(int x) {
        if (parent_arr[x] != x) parent_arr[x] = find(parent_arr[x]);
        return parent_arr[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank_arr[px] < rank_arr[py]) swap(px, py);
        parent_arr[py] = px;
        if (rank_arr[px] == rank_arr[py]) rank_arr[px]++;
        return true;
    }
};

int min_operations_optimal(int total_nodes, vector<vector<int>>& edges) {
    DSU dsu_obj(total_nodes);
    int redundant_edges = 0;
    for (auto& edge : edges) {
        if (!dsu_obj.unite(edge[0], edge[1])) redundant_edges++;
    }
    int components = 0;
    for (int i = 0; i < total_nodes; i++) {
        if (dsu_obj.find(i) == i) components++;
    }
    return (redundant_edges >= components - 1) ? components - 1 : -1;
}

int main() {
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}};
    cout << min_operations_optimal(4, edges) << endl;
    return 0;
}
