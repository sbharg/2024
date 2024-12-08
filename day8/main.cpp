#include <bits/stdc++.h>
using namespace std;

// trim from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v") {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v") {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v") {
    return ltrim(rtrim(s, t), t);
}

using ll = int64_t;
using data_t = vector<vector<char>>;

data_t parse(const string& filenme) {
    ifstream file(filenme);
    string line;
    
    data_t data;
    while (getline(file, line)) {
        line = trim(line);
        vector<char> row;
        for (const char& c : line) {
            row.push_back(c);
        }
        data.push_back(row);
    }
    return data;
}

void print_board(const data_t& info, const vector<pair<int, int>>& antinodes) {
    vector<vector<string>> board;
    for (const auto& row : info) {
        vector<string> r;
        for (const char& c : row) {
            r.push_back(string(1, c));
        }
        board.push_back(r);
    }

    string antinode = "\033[1;32m#\033[0m";
    for (const auto& [i, j] : antinodes) {
        if (board[i][j] == ".") { board[i][j] = antinode; } 
        else { board[i][j] = "\033[1;4;32m" + board[i][j] + "\033[0m"; }
    }

    for (const auto& row : board) {
        for (const string& s : row) {
            cout << s;
        }
        cout << endl;
    }
}

int part1(const data_t& info, const int n, const int m, const unordered_map<char, vector<pair<int, int>>>& antennas) { 
    auto hash = [](const std::pair<int, int>& p){ return p.first * 31 + p.second; };
    auto valid_pos = [](const pair<int, int>& p, int n, int m) {
        return p.first >= 0 && p.first < n && p.second >= 0 && p.second < m;
    };

    unordered_set<pair<int, int>, decltype(hash)> antinodes;
    for (const auto& [freq, positions] : antennas) {
        if (positions.size() < 2) { continue; }
        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = i+1; j < positions.size(); j++) {
                int vert = abs(positions[i].first - positions[j].first);
                int horz = abs(positions[i].second - positions[j].second);

                pair<int, int> antenna1 = max(positions[i], positions[j], [](const pair<int, int>& a, const pair<int, int>& b) {
                    return a.second < b.second;
                });
                pair<int, int> antenna2 = (antenna1 == positions[i]) ? positions[j] : positions[i];
                float slope = (antenna2.first - antenna1.first) / static_cast<float>(antenna1.second - antenna2.second);

                pair<int, int> antinode1 = antenna1, antinode2 = antenna2;

                antinode1.first += (slope >= 0.0) ? -vert : vert;
                antinode1.second += horz;
                if (valid_pos(antinode1, n, m)) { antinodes.insert(antinode1); }

                antinode2.first += (slope >= 0.0) ? vert : -vert;
                antinode2.second -= horz;
                if (valid_pos(antinode2, n, m)) { antinodes.insert(antinode2); }
            }
        }
    }
    
    // vector<pair<int, int>> antinodes_v(antinodes.begin(), antinodes.end());
    // print_board(info, antinodes_v);
    return antinodes.size();
}

int part2(const data_t& info, const int n, const int m, const unordered_map<char, vector<pair<int, int>>>& antennas) {
    auto hash = [](const std::pair<int, int>& p){ return p.first * 31 + p.second; };
    auto valid_pos = [](const pair<int, int>& p, int n, int m) {
        return p.first >= 0 && p.first < n && p.second >= 0 && p.second < m;
    };

    unordered_set<pair<int, int>, decltype(hash)> antinodes;
    for (const auto& [freq, positions] : antennas) {
        if (positions.size() < 2) { continue; }
        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = i+1; j < positions.size(); j++) {
                int vert = abs(positions[i].first - positions[j].first);
                int horz = abs(positions[i].second - positions[j].second);

                pair<int, int> antenna1 = max(positions[i], positions[j], [](const pair<int, int>& a, const pair<int, int>& b) {
                    return a.second < b.second;
                });
                pair<int, int> antenna2 = (antenna1 == positions[i]) ? positions[j] : positions[i];
                float slope = (antenna2.first - antenna1.first) / static_cast<float>(antenna1.second - antenna2.second);

                pair<int, int> antinode1 = antenna1, antinode2 = antenna2;
                while (valid_pos(antinode1, n, m)) {
                    antinodes.insert(antinode1);
                    antinode1.first += (slope >= 0.0) ? -vert : vert;
                    antinode1.second += horz;
                }
                while (valid_pos(antinode2, n, m)) {
                    antinodes.insert(antinode2);
                    antinode2.first += (slope >= 0.0) ? vert : -vert;
                    antinode2.second -= horz;
                }
            }
        }
    }
    
    vector<pair<int, int>> antinodes_v(antinodes.begin(), antinodes.end());
    print_board(info, antinodes_v);
    return antinodes.size();
}

int main(int argc, char** argv) {
    string filename = argv[1];
    data_t data = parse(filename);

    int n = data.size(), m = data[0].size();
    unordered_map<char, vector<pair<int, int>>> antennas;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            const char c = data[i][j];
            if (c != '.') { antennas[c].push_back({i, j}); }
        }
    }

    int part1_ans = part1(data, n, m, antennas);
    int part2_ans = part2(data, n, m, antennas);
    cout << "[Part 1]: " << part1_ans << endl;
    cout << "[Part 2]: " << part2_ans << endl;
    return 0;
}