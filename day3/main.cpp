#include <bits/stdc++.h>
using namespace std;

int parse_mul(const string& expr) {
    string nums = expr.substr(4, expr.size() - 1);
    int a = stoi(nums.substr(0, nums.find(',')));
    int b = stoi(nums.substr(nums.find(',') + 1, nums.size() - 1));
    return a * b;
}

int part1(const string& filename) {
    ifstream file(filename);
    string line;
    
    int sum = 0;
    std::regex pattern("mul\\(\\d*,\\d*\\)"); // Match whole words
    while (getline(file, line)) {
        std::sregex_iterator it(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        for (; it != end; ++it) {
            std::smatch match = *it;
            sum += parse_mul(match.str());
        }
    }
    return sum;
}

int part2(const string& filename) {
    ifstream file(filename);
    string line;
    
    int sum = 0;
    bool add = true;
    std::regex pattern("mul\\(\\d*,\\d*\\)|do\\(\\)|don't\\(\\)");
    while (getline(file, line)) {
        std::sregex_iterator it(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        for (; it != end; ++it) {
            std::smatch match = *it;
            if (match.str() == "do()") { add = true; }
            else if (match.str() == "don't()") { add = false; }
            else { sum += add ? parse_mul(match.str()) : 0; }
        }
    }
    return sum;
}

int main(int argc, char** argv) {
    string filename = argv[1];

    int part1_ans = part1(filename);
    int part2_ans = part2(filename);
    cout << "[Part 1]: " << part1_ans << endl;
    cout << "[Part 2]: " << part2_ans << endl;
    return 0;
}