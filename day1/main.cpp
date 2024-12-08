#include <bits/stdc++.h>
using namespace std;

inline pair<int, int> split_pair(const string& input, const string& delimiter = " ") {
    pair<int, int> ret;

    size_t pos = 0, lpos = 0;
    size_t dlen = delimiter.length();

    pos = input.find(delimiter, lpos);
    ret.first = stoi(input.substr(lpos, pos - lpos));
    lpos = pos + dlen;
    ret.second = stoi(input.substr(lpos));

    return ret;
}

int part1(const string& filename) {
    ifstream file(filename);
    std::string line;

    std::vector<int> l1({}), l2({});
    while (std::getline(file, line)) {
        pair<int, int> p = split_pair(line);
        l1.push_back(p.first);
        l2.push_back(p.second);
    }
    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());

    int distance = 0;
    for (size_t i = 0; i < l1.size(); i++) {
        distance += abs(l1[i] - l2[i]);
    }
    return distance;
}

int part2(const string& filename) {
    ifstream file(filename);
    std::string line;

    std::vector<int> l1({});
    std::unordered_map<int, int> l2_freq;
    while (std::getline(file, line)) {
        pair<int, int> p = split_pair(line);
        l1.push_back(p.first);
        l2_freq[p.second]++;
    }

    int similarity = 0;
    for (size_t i = 0; i < l1.size(); i++) {
        if (l2_freq.find(l1[i]) != l2_freq.end()) {
            similarity += l1[i] * l2_freq[l1[i]];
        }
    }
    return similarity;
}

int main(int argc, char** argv) {
    string filename = argv[1];

    int part1_ans = part1(filename);
    int part2_ans = part2(filename);
    cout << "[Part 1]: " << part1_ans << endl;
    cout << "[Part 2]: " << part2_ans << endl;
    return 0;
}