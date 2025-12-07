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

int max_island_size_optimal(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    DSU dsu_obj(rows * cols);
    vector<int> island_size(rows * cols, 0);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                island_size[r * cols + c] = 1;
            }
        }
    }

    int dirs[] = {-1, 1, 0, 0}, dirc[] = {0, 0, -1, 1};

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                for (int d = 0; d < 4; d++) {
                    int nr = r + dirs[d], nc = c + dirc[d];
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                        dsu_obj.unite(r * cols + c, nr * cols + nc);
                    }
                }
            }
        }
    }

    int max_size = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 0) {
                int merged_size = 1;
                set<int> neighbors;
                for (int d = 0; d < 4; d++) {
                    int nr = r + dirs[d], nc = c + dirc[d];
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                        neighbors.insert(dsu_obj.find(nr * cols + nc));
                    }
                }
                for (int root : neighbors) merged_size += island_size[root];
                max_size = max(max_size, merged_size);
            }
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                max_size = max(max_size, island_size[dsu_obj.find(r * cols + c)]);
            }
        }
    }

    return max_size;
}

int main() {
    vector<vector<int>> grid = {{1, 0}, {0, 1}};
    cout << max_island_size_optimal(grid) << endl;
    return 0;
}
