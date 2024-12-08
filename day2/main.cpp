#include <bits/stdc++.h>
using namespace std;

bool is_report_safe(const vector<int>& nums) {
    bool inc = true, dec = true;
    for (size_t i = 1; i < nums.size(); i++) {
        int gap = nums[i] - nums[i - 1];
        if (gap == 0 || gap > 3 || gap < -3) { return false; }

        if (gap < 0) { inc = false; }
        else if (gap > 0) { dec = false; }

        if (!inc && !dec) { return false; }
    }
    return true;
}

inline bool is_report_safe(const string& line) {
    stringstream ss(line);
    string num;

    vector<int> nums;
    while (getline(ss, num, ' ')) {
        nums.push_back(stoi(num));
    }

    return is_report_safe(nums);
}

int part1(const string& filename) {
    ifstream file(filename);
    string line;

    int safe = 0;
    while (getline(file, line)) {
        safe += (is_report_safe(line)) ? 1 : 0;
    }
    return safe;
}

bool is_report_safe_tol(const vector<int>& nums) {
    // Remove each level and check if the report is safe
    for (size_t i = 0; i < nums.size(); i++) {
        vector<int> copy = nums;
        copy.erase(copy.begin() + i);
        if (is_report_safe(copy)) { return true; }
    }
    return false;
}

inline bool is_report_safe_tol(const string& line) {
    stringstream ss(line);
    string num;

    vector<int> nums;
    while (getline(ss, num, ' ')) {
        nums.push_back(stoi(num));
    }

    return is_report_safe_tol(nums);
}

int part2(const string& filename) {
    ifstream file(filename);
    string line;

    int safe = 0;
    while (getline(file, line)) {
        safe += (is_report_safe_tol(line)) ? 1 : 0;
    }
    return safe;
}

int main(int argc, char** argv) {
    string filename = argv[1];

    int part1_ans = part1(filename);
    int part2_ans = part2(filename);
    cout << "[Part 1]: " << part1_ans << endl;
    cout << "[Part 2]: " << part2_ans << endl;
    return 0;
}