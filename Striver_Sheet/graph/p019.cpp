#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> word_ladder_ii_optimal(string start_word, string target_word, vector<string>& word_list) {
    unordered_set<string> word_set(word_list.begin(), word_list.end());
    vector<vector<string>> result_paths;
    vector<string> current_path = {start_word};

    unordered_map<string, vector<string>> adj_map;

    function<bool(void)> build_graph = [&]() {
        unordered_set<string> current_level, next_level;
        current_level.insert(start_word);

        while (!current_level.empty() && !current_level.count(target_word)) {
            for (const string& word : current_level) word_set.erase(word);
            next_level.clear();

            for (const string& word : current_level) {
                string temp_word = word;
                for (int i = 0; i < temp_word.length(); i++) {
                    char original = temp_word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        temp_word[i] = c;
                        if (word_set.count(temp_word)) {
                            adj_map[word].push_back(temp_word);
                            next_level.insert(temp_word);
                        }
                    }
                    temp_word[i] = original;
                }
            }
            current_level = next_level;
        }
        return current_level.count(target_word) > 0;
    };

    if (!build_graph()) return result_paths;

    function<void(string)> dfs_find_paths = [&](const string& curr_word) {
        if (curr_word == target_word) {
            result_paths.push_back(current_path);
            return;
        }
        for (const string& next_word : adj_map[curr_word]) {
            current_path.push_back(next_word);
            dfs_find_paths(next_word);
            current_path.pop_back();
        }
    };

    dfs_find_paths(start_word);
    return result_paths;
}

int main() {
    string start = "der", target = "dfs";
    vector<string> wordlist = {"des", "der", "dfr", "dgt", "dfs"};
    auto paths = word_ladder_ii_optimal(start, target, wordlist);
    for (auto& path : paths) {
        for (string& w : path) cout << w << " ";
        cout << endl;
    }
    return 0;
}
