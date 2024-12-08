#include <bits/stdc++.h>
using namespace std;

// trim from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

pair<unordered_map<int, unordered_set<int>>, vector<vector<int>>> parse_input(const string filename) {
    ifstream file(filename);
    string line;

    unordered_map<int, unordered_set<int>> update_rules;
    vector<vector<int>> updates;

    getline(file, line);
    while (line != "break") {
        int n1 = stoi(line.substr(0, line.find('|')));
        int n2 = stoi(line.substr(line.find('|')+1));
        update_rules[n1].insert(n2);
        getline(file, line);
    }

    while (getline(file, line)) {
        vector<int> update;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            update.push_back(stoi(token));
        }
        updates.push_back(update);
    }

    return {update_rules, updates};
}

int part1(unordered_map<int, unordered_set<int>>& rules, vector<vector<int>> updates) { 
    vector<vector<int>> valid_updates;
    for (auto& update : updates) {
        reverse(update.begin(), update.end());

        bool valid = true;
        for (size_t i = 0; i < update.size() && valid; i++) {
            for (size_t j = i+1; j < update.size(); j++) {
                if (rules[update[i]].contains(update[j])) {
                    valid = false;
                    break;
                }
            }
        }

        if (valid) {
            valid_updates.push_back(update);
        }
    }

    int sum = 0;
    for (const auto& update : valid_updates) {
        // Add midpoint of the update
        sum += update[update.size()/2];
    }
    return sum;
}

int part2(unordered_map<int, unordered_set<int>>& rules, vector<vector<int>> updates) {
    vector<vector<int>> invalid_updates;
    for (vector<int>& update : updates) {
        reverse(update.begin(), update.end());

        bool valid = true;
        for (size_t i = 0; i < update.size() && valid; i++) {
            for (size_t j = i+1; j < update.size(); j++) {
                if (rules[update[i]].contains(update[j])) {
                    valid = false;
                    break;
                }
            }
        }

        if (!valid) { 
            //reverse(update.begin(), update.end());
            invalid_updates.push_back(update); 
        }
    }

    int sum = 0;
    // Correct the page orderings
    for (auto& update : invalid_updates) { 
        unordered_map<int, unordered_set<int>> children;

        for (size_t i = 0; i < update.size(); i++) {
            for (size_t j = 0; j < update.size(); j++) {
                if (j != i && rules[update[i]].contains(update[j])) {
                    children[update[i]].insert(update[j]);
                }
            }
        }

        // Sort the updates by the number of children
        sort(update.begin(), update.end(), [&children](const int& a, const int& b) {
            return children[a].size() > children[b].size();
        });

        sum += update[update.size()/2];
    }

    return sum;
}

int main(int argc, char** argv) {
    string filename = argv[1];
    auto [update_rules, updates] = parse_input(filename);

    int part1_ans = part1(update_rules, updates);
    int part2_ans = part2(update_rules, updates);
    cout << "[Part 1]: " << part1_ans << endl;
    cout << "[Part 2]: " << part2_ans << endl;
    return 0;
}