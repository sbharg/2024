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

using ll = uint64_t;

vector<pair<ll, vector<ll>>> parse(const string& filenme) {
    ifstream file(filenme);
    string line;
    
    vector<pair<ll, vector<ll>>> data;
    while (getline(file, line)) {
        line = trim(line);
        ll key = 0;
        vector<ll> values;

        key = stoull(line.substr(0, line.find(":")));
        stringstream ss(line.substr(line.find(":") + 2));
        string token;
        while (getline(ss, token, ' ')) { 
            values.push_back(stoull(token)); 
        }
        data.push_back({key, values});
    }
    return data;
}

ll part1(vector<pair<ll, vector<ll>>> data) { 
    ll calibration_sum = 0;

    for (const auto& [key, values] : data) {
        bool valid = false;
        vector<ll> possible_vals({values[0]});

        for (size_t i = 1; i < values.size(); i++) {
            vector<ll> temp;
            for (const ll& val : possible_vals) {
                if (val + values[i] <= key) {
                    if (i == values.size() - 1 && val + values[i] == key) {
                        valid = true;
                        break;
                    }
                    temp.push_back(val + values[i]);
                }
                if (val * values[i] <= key) {
                    if (i == values.size() - 1 && val * values[i] == key) {
                        valid = true;
                        break;
                    }
                    temp.push_back(val * values[i]);
                }
            }
            if (valid) break;
            possible_vals = temp;
        }

        calibration_sum += (valid) ? key : 0;
    }
    return calibration_sum;
}

ll part2(vector<pair<ll, vector<ll>>> data) {
    ll calibration_sum = 0;

    for (const auto& [key, values] : data) {
        bool valid = false;
        vector<ll> possible_vals({values[0]});

        for (size_t i = 1; i < values.size(); i++) {
            vector<ll> temp;
            for (const ll& val : possible_vals) {
                if (val + values[i] <= key) {
                    if (i == values.size() - 1 && val + values[i] == key) {
                        valid = true;
                        break;
                    }
                    temp.push_back(val + values[i]);
                }
                
                if (val * values[i] <= key) {
                    if (i == values.size() - 1 && val * values[i] == key) {
                        valid = true;
                        break;
                    }
                    temp.push_back(val * values[i]); 
                }

                string s = to_string(val) + to_string(values[i]);
                if (stoull(s) <= key) {
                    if (i == values.size() - 1 && stoull(s) == key) {
                        valid = true;
                        break;
                    }
                    temp.push_back(stoull(s));
                }
            }
            if (valid) break;
            possible_vals = temp;
        }

        calibration_sum += (valid) ? key : 0;
    }
    return calibration_sum;
}

int main(int argc, char** argv) {
    string filename = argv[1];
    vector<pair<ll, vector<ll>>> data = parse(filename);

    // for (const auto& [key, values] : data) {
    //     cout << key << ": ";
    //     for (const auto& value : values) {
    //         cout << value << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    ll part1_ans = part1(data);
    ll part2_ans = part2(data);
    cout << "[Part 1]: " << part1_ans << endl;
    cout << "[Part 2]: " << part2_ans << endl;
    return 0;
}