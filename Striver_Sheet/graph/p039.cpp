#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        p[px] = py;
        return true;
    }
};

vector<int> islands_online_optimal(int rows, int cols, vector<vector<int>>& operations_list) {
    DSU dsu_obj(rows * cols);
    vector<bool> land_cell(rows * cols, false);
    vector<int> island_counts;
    int islands = 0;

    int directions[] = {-1, 1, 0, 0}, dirc[] = {0, 0, -1, 1};

    for (auto& op : operations_list) {
        int r = op[0], c = op[1];
        int cell_idx = r * cols + c;

        if (land_cell[cell_idx]) {
            island_counts.push_back(islands);
            continue;
        }

        land_cell[cell_idx] = true;
        islands++;

        for (int d = 0; d < 4; d++) {
            int nr = r + directions[d], nc = c + dirc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && land_cell[nr * cols + nc]) {
                int neighbor_idx = nr * cols + nc;
                if (dsu_obj.unite(cell_idx, neighbor_idx)) {
                    islands--;
                }
            }
        }

        island_counts.push_back(islands);
    }

    return island_counts;
}

int main() {
    vector<vector<int>> ops = {{1, 1}, {0, 1}, {3, 3}, {3, 4}};
    auto res = islands_online_optimal(4, 5, ops);
    for (int count : res) cout << count << " ";
    cout << endl;
    return 0;
}
