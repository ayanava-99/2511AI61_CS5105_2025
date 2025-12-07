#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int x, int y) { p[find(x)] = find(y); }
};

vector<vector<string>> merge_accounts_optimal(vector<vector<string>>& accounts_list) {
    DSU dsu_obj(accounts_list.size());
    map<string, int> email_to_account;

    for (int i = 0; i < accounts_list.size(); i++) {
        for (int j = 1; j < accounts_list[i].size(); j++) {
            string email = accounts_list[i][j];
            if (email_to_account.count(email)) {
                dsu_obj.unite(i, email_to_account[email]);
            } else {
                email_to_account[email] = i;
            }
        }
    }

    map<int, set<string>> component_emails;
    for (int i = 0; i < accounts_list.size(); i++) {
        int root = dsu_obj.find(i);
        for (int j = 1; j < accounts_list[i].size(); j++) {
            component_emails[root].insert(accounts_list[i][j]);
        }
    }

    vector<vector<string>> result_merged;
    for (auto& [root, emails] : component_emails) {
        vector<string> merged_account = {accounts_list[root][0]};
        for (const string& email : emails) {
            merged_account.push_back(email);
        }
        result_merged.push_back(merged_account);
    }

    return result_merged;
}

int main() {
    vector<vector<string>> accounts = {{"John", "johnsmith@mail.com", "john_newyork@mail.com"}, 
                                       {"John", "johnsmith@mail.com", "john00@mail.com"}, 
                                       {"Mary", "mary@mail.com"}, 
                                       {"John", "johnnybravo@mail.com"}};
    auto merged = merge_accounts_optimal(accounts);
    for (auto& acc : merged) {
        for (string& s : acc) cout << s << " ";
        cout << endl;
    }
    return 0;
}
