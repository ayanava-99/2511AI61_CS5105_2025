#include <bits/stdc++.h>
using namespace std;

int min_multiplications_optimal(vector<int>& mult_arr, int start_val, int end_val) {
    const int MOD = 100000;
    if (start_val == end_val) return 0;

    vector<int> dist(MOD, INT_MAX);
    queue<int> bfs_q;

    dist[start_val] = 0;
    bfs_q.push(start_val);

    while (!bfs_q.empty()) {
        int curr_val = bfs_q.front();
        bfs_q.pop();

        for (int mult_num : mult_arr) {
            int next_val = (1LL * curr_val * mult_num) % MOD;
            if (dist[next_val] > dist[curr_val] + 1) {
                dist[next_val] = dist[curr_val] + 1;
                if (next_val == end_val) return dist[next_val];
                bfs_q.push(next_val);
            }
        }
    }

    return -1;
}

int main() {
    vector<int> arr = {2, 5, 7};
    cout << min_multiplications_optimal(arr, 3, 30) << endl;
    return 0;
}
