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
using data_t = vector<int>;

data_t parse(const string& filenme) {
    ifstream file(filenme);
    string line;
    
    data_t data;
    while (getline(file, line)) {
        line = trim(line);
    }
    return data;
}

int part1(data_t info) { 
    return 0;
}

int part2(data_t info) {
    return 0;
}

int main(int argc, char** argv) {
    string filename = argv[1];
    data_t data = parse(filename);

    int part1_ans = part1(data);
    int part2_ans = part2(data);
    cout << "[Part 1]: " << part1_ans << endl;
    cout << "[Part 2]: " << part2_ans << endl;
    return 0;
}