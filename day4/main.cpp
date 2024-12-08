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

int search_for_string(const vector<vector<char>>& word_search, const string& word, int i, int j) {
    int n = word_search.size(), m = word_search[0].size();
    auto is_valid = [&](int i, int j) {
        return i >= 0 && i < n && j >= 0 && j < m;
    };

    int matches = 0;

    bool match_up = true, match_down = true, match_left = true, match_right = true;
    bool match_up_left = true, match_up_right = true, match_down_left = true, match_down_right = true;
    for (size_t x = 1; x < word.length(); x++) {
        if (!is_valid(i+x, j) || word_search[i+x][j] != word[x]) {
            match_down = false;
        }
        if (!is_valid(i-x, j) || word_search[i-x][j] != word[x]) {
            match_up = false;
        }
        if (!is_valid(i, j+x) || word_search[i][j+x] != word[x]) {
            match_right = false;
        }
        if (!is_valid(i, j-x) || word_search[i][j-x] != word[x]) {
            match_left = false;
        }
        if (!is_valid(i-x, j-x) || word_search[i-x][j-x] != word[x]) {
            match_up_left = false;
        }
        if (!is_valid(i-x, j+x) || word_search[i-x][j+x] != word[x]) {
            match_up_right = false;
        }
        if (!is_valid(i+x, j+x) || word_search[i+x][j+x] != word[x]) {
            match_down_right = false;
        }
        if (!is_valid(i+x, j-x) || word_search[i+x][j-x] != word[x]) {
            match_down_left = false;
        }
    }
    matches += (match_up) ? 1 : 0;
    matches += (match_down) ? 1 : 0;
    matches += (match_left) ? 1 : 0;
    matches += (match_right) ? 1 : 0;
    matches += (match_up_left) ? 1 : 0;
    matches += (match_up_right) ? 1 : 0;
    matches += (match_down_left) ? 1 : 0;
    matches += (match_down_right) ? 1 : 0;

    return matches;
}

int part1(const vector<vector<char>>& word_search) { 
    int matches = 0;
    int n = word_search.size(), m = word_search[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (word_search[i][j] == 'X') { 
                matches += search_for_string(word_search, "XMAS", i, j); 
            }
        }
    }
    return matches;
}

bool search_for_cross(const vector<vector<char>>& word_search, int i, int j) {
    int n = word_search.size(), m = word_search[0].size();
    auto is_valid = [&](int i, int j) {
        return i >= 0 && i < n && j >= 0 && j < m;
    };

    bool match_up_left = true, match_up_right = true, match_down_left = true, match_down_right = true;
    if (!is_valid(i-1, j-1) || (word_search[i-1][j-1] != 'M' && word_search[i-1][j-1] != 'S')) {
        match_up_left = false;
    }
    if (!is_valid(i+1, j+1) || (word_search[i+1][j+1] != 'M' && word_search[i+1][j+1] != 'S')) {
        match_down_right = false;
    }
    
    if (!is_valid(i-1, j+1) || (word_search[i-1][j+1] != 'M' && word_search[i-1][j+1] != 'S')) {
        match_up_right = false;
    }
    if (!is_valid(i+1, j-1) || (word_search[i+1][j-1] != 'M' && word_search[i+1][j-1] != 'S')) {
        match_down_left = false;
    }
    
    bool diag_one = false, diag_two = false;
    if (match_up_left && match_down_right) { 
        if (word_search[i-1][j-1] == 'M' && word_search[i+1][j+1] == 'S') { diag_one = true; }
        else if (word_search[i-1][j-1] == 'S' && word_search[i+1][j+1] == 'M') { diag_one = true; }
    }
    if (match_up_right && match_down_left) { 
        if (word_search[i-1][j+1] == 'M' && word_search[i+1][j-1] == 'S') { diag_two = true; }
        else if (word_search[i-1][j+1] == 'S' && word_search[i+1][j-1] == 'M') { diag_two = true; }
    }

    return diag_one && diag_two;
}

int part2(vector<vector<char>>& word_search) {
    int n = word_search.size(), m = word_search[0].size();
    vector<vector<bool>> mask(n, vector<bool>(m, false));

    int matches = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (word_search[i][j] == 'A') { 
                matches += (search_for_cross(word_search, i, j)) ? 1 : 0; 
            }
        }
    }
    return matches;
}

vector<vector<char>> parse_word_search(string filename) {
    vector<vector<char>> word_search;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<char> row;
        line = trim(line);
        for (char c : line) {
            row.push_back(c);
        }
        word_search.push_back(row);
    }
    return word_search;
}

int main(int argc, char** argv) {
    string filename = argv[1];
    vector<vector<char>> word_search = parse_word_search(filename);

    int part1_ans = part1(word_search);
    int part2_ans = part2(word_search);
    cout << "[Part 1]: " << part1_ans << endl;
    cout << "[Part 2]: " << part2_ans << endl;
    return 0;
}