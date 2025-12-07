#include <bits/stdc++.h>
using namespace std;

string alien_dict_optimal(vector<string>& alien_words, int alphabet_count) {
    vector<vector<int>> adj_graph(alphabet_count);
    vector<int> in_degree(alphabet_count, 0);

    for (int i = 0; i < alien_words.size() - 1; i++) {
        string word1 = alien_words[i], word2 = alien_words[i + 1];
        int min_len = min(word1.length(), word2.length());

        for (int j = 0; j < min_len; j++) {
            if (word1[j] != word2[j]) {
                int u = word1[j] - 'a', v = word2[j] - 'a';
                if (find(adj_graph[u].begin(), adj_graph[u].end(), v) == adj_graph[u].end()) {
                    adj_graph[u].push_back(v);
                    in_degree[v]++;
                }
                break;
            }
        }
    }

    queue<int> char_queue;
    for (int c = 0; c < alphabet_count; c++) {
        if (in_degree[c] == 0) char_queue.push(c);
    }

    string result = "";
    while (!char_queue.empty()) {
        int curr_char = char_queue.front();
        char_queue.pop();
        result += (char)('a' + curr_char);

        for (int neighbor : adj_graph[curr_char]) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) char_queue.push(neighbor);
        }
    }

    return result;
}

int main() {
    vector<string> words = {"baa", "abcd", "abca", "cab", "cad"};
    cout << alien_dict_optimal(words, 4) << endl;
    return 0;
}
