#include <bits/stdc++.h>
using namespace std;

int word_ladder_optimal(string start_word, string target_word, vector<string>& word_list) {
    unordered_set<string> word_set(word_list.begin(), word_list.end());
    if (!word_set.count(target_word)) return 0;

    queue<pair<string, int>> bfs_q;
    bfs_q.push({start_word, 1});
    word_set.erase(start_word);

    while (!bfs_q.empty()) {
        auto [curr_word, step_count] = bfs_q.front();
        bfs_q.pop();

        for (int idx = 0; idx < curr_word.length(); idx++) {
            char original_char = curr_word[idx];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                curr_word[idx] = ch;
                if (curr_word == target_word) return step_count + 1;
                if (word_set.count(curr_word)) {
                    word_set.erase(curr_word);
                    bfs_q.push({curr_word, step_count + 1});
                }
            }
            curr_word[idx] = original_char;
        }
    }
    return 0;
}

int main() {
    string start = "der", target = "dfs";
    vector<string> wordlist = {"des", "der", "dfr", "dgt", "dfs"};
    cout << word_ladder_optimal(start, target, wordlist) << endl;
    return 0;
}
