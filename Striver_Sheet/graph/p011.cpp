#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, rnk;
    DSU(int n) : parent(n), rnk(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rnk[px] < rnk[py]) swap(px, py);
        parent[py] = px;
        if (rnk[px] == rnk[py]) rnk[px]++;
        return true;
    }
};

int max_stones_removable_optimal(vector<vector<int>>& stones_pos) {
    DSU dsu_obj(stones_pos.size());
    map<int, int> row_map, col_map;

    for (int i = 0; i < stones_pos.size(); i++) {
        int r = stones_pos[i][0], c = stones_pos[i][1];
        if (!row_map.count(r)) row_map[r] = i;
        if (!col_map.count(c)) col_map[c] = i;
        dsu_obj.unite(i, row_map[r]);
        dsu_obj.unite(i, col_map[c]);
    }

    set<int> components;
    for (int i = 0; i < stones_pos.size(); i++) {
        components.insert(dsu_obj.find(i));
    }
    return stones_pos.size() - components.size();
}

int main() {
    vector<vector<int>> stones = {{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}};
    cout << max_stones_removable_optimal(stones) << endl;
    return 0;
}
