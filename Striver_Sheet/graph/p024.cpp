#include <bits/stdc++.h>
using namespace std;

vector<int> course_order_optimal(int total_courses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj_list(total_courses);
    vector<int> indegree_array(total_courses, 0);

    for (auto& prereq : prerequisites) {
        adj_list[prereq[1]].push_back(prereq[0]);
        indegree_array[prereq[0]]++;
    }

    queue<int> course_queue;
    for (int course = 0; course < total_courses; course++) {
        if (indegree_array[course] == 0) {
            course_queue.push(course);
        }
    }

    vector<int> course_order;
    while (!course_queue.empty()) {
        int curr_course = course_queue.front();
        course_queue.pop();
        course_order.push_back(curr_course);

        for (int next_course : adj_list[curr_course]) {
            indegree_array[next_course]--;
            if (indegree_array[next_course] == 0) {
                course_queue.push(next_course);
            }
        }
    }

    return course_order.size() == total_courses ? course_order : vector<int>();
}

int main() {
    int n = 4;
    vector<vector<int>> prereq = {{1, 0}, {2, 1}, {3, 2}};
    auto res = course_order_optimal(n, prereq);
    for (int c : res) cout << c << " ";
    cout << endl;
    return 0;
}
