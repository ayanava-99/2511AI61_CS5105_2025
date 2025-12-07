#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> p, r;
    DSU(int n) : p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (r[px] < r[py]) swap(px, py);
        p[py] = px;
        if (r[px] == r[py]) r[px]++;
        return true;
    }
};

int kruskal_mst_optimal(int total_nodes, vector<vector<int>>& edges_list) {
    sort(edges_list.begin(), edges_list.end(), [](const auto& a, const auto& b) {
        return a[2] < b[2];
    });

    DSU dsu_obj(total_nodes);
    int mst_weight = 0, edges_added = 0;

    for (auto& edge : edges_list) {
        if (dsu_obj.unite(edge[0], edge[1])) {
            mst_weight += edge[2];
            edges_added++;
            if (edges_added == total_nodes - 1) break;
        }
    }

    return mst_weight;
}

int main() {
    vector<vector<int>> edges = {{0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8}, {1, 4, 5}, {4, 2, 7}};
    cout << kruskal_mst_optimal(5, edges) << endl;
    return 0;
}
