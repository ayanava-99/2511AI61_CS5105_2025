#include <bits/stdc++.h>
using namespace std;

bool can_finish_all_tasks_optimal(int total_tasks, vector<vector<int>>& task_deps) {
    vector<vector<int>> adj_graph(total_tasks);
    vector<int> in_degree(total_tasks, 0);

    for (auto& dep : task_deps) {
        adj_graph[dep[1]].push_back(dep[0]);
        in_degree[dep[0]]++;
    }

    queue<int> task_queue;
    for (int task = 0; task < total_tasks; task++) {
        if (in_degree[task] == 0) {
            task_queue.push(task);
        }
    }

    int task_count = 0;
    while (!task_queue.empty()) {
        int curr_task = task_queue.front();
        task_queue.pop();
        task_count++;

        for (int next_task : adj_graph[curr_task]) {
            in_degree[next_task]--;
            if (in_degree[next_task] == 0) {
                task_queue.push(next_task);
            }
        }
    }

    return task_count == total_tasks;
}

int main() {
    int n = 4;
    vector<vector<int>> deps = {{1, 2}, {4, 3}, {2, 4}, {4, 1}};
    cout << (can_finish_all_tasks_optimal(n, deps) ? "Yes" : "No") << endl;
    return 0;
}
