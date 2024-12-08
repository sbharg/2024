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

pair<vector<vector<int>>, pair<int, int>> parse(const string& filenme) {
    ifstream file(filenme);
    string line;
    
    vector<vector<int>> map;
    pair<int, int> start;
    int i = 0;
    while (getline(file, line)) {
        line = trim(line);
        vector<int> row;
        for (size_t j = 0; j < line.length(); j++) {
            if (line[j] == '.') { row.push_back(0); } 
            else if (line[j] == '#') { row.push_back(1); }
            else if (line[j] == '^') { 
                row.push_back(2); 
                start = {i, j};
            }
        }
        map.push_back(row);
        i++;
    }
    return {map, start};
}

pair<int, int> part1(vector<vector<int>> map, pair<int, int>& start) { 
    int n = map.size(), m = map[0].size();
    enum class Direction { 
        UP, RIGHT, DOWN, LEFT 
    };
    unordered_map<Direction, pair<int, int>> dir_map = {
        {Direction::UP, {-1, 0}},
        {Direction::RIGHT, {0, 1}},
        {Direction::DOWN, {1, 0}},
        {Direction::LEFT, {0, -1}}
    };

    Direction dir = Direction::UP;
    pair<int, int> curr = start;
    int unique = 1;
    int n_steps = 0;

    while (curr.first >= 0 && curr.first < n && curr.second >= 0 && curr.second < m) {
        curr = {curr.first + dir_map[dir].first, curr.second + dir_map[dir].second};
        if (curr.first >= 0 && curr.first < n && curr.second >= 0 && curr.second < m) {
            // Free space
            if (map[curr.first][curr.second] == 0) { 
                map[curr.first][curr.second] = 2;
                unique++;
            }
            // Obstacle
            else if (map[curr.first][curr.second] == 1) {
                curr = {curr.first - dir_map[dir].first, curr.second - dir_map[dir].second};
                dir = static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
            }
            n_steps++;
        }
    }
    return {unique, n_steps};
}

void print_obstacles(
    const vector<pair<int, int>>& obstacles, 
    const vector<pair<int, int>>& potential_square, 
    const pair<int, int>& start,
    int n, int m
) {
    vector<vector<string>> grid(n, vector<string>(m, "."));
    grid[start.first][start.second] = "\033[1;32m^\033[0m";
    for (const auto& obs : obstacles) {
        grid[obs.first][obs.second] = "#";
    }

    string obstacle = "\033[1;31m#\033[0m";
    for (const auto& obs : potential_square) {
       grid[obs.first][obs.second] = obstacle;
    }
    grid[potential_square.back().first][potential_square.back().second] = "\033[1;4;31m#\033[0m";

    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[0].size(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

void simulate(
    const vector<pair<int, int>>& obstacles, 
    const pair<int, int>& start,
    int n, int m,
    int max_steps
) {
    vector<vector<string>> map(n, vector<string>(m, "."));
    string cursor_start = "\033[1;34m^\033[0m";
    map[start.first][start.second] = cursor_start;

    string obstacle = "\033[1;31m#\033[0m";
    for (const auto& obs : obstacles) {
        map[obs.first][obs.second] = obstacle;
    }

    enum class Direction { 
        UP, RIGHT, DOWN, LEFT 
    };
    unordered_map<Direction, pair<int, int>> dir_map = {
        {Direction::UP, {-1, 0}},
        {Direction::RIGHT, {0, 1}},
        {Direction::DOWN, {1, 0}},
        {Direction::LEFT, {0, -1}}
    };
    unordered_map<Direction, string> dir_cursor = {
        {Direction::UP, "\033[1;32m^\033[0m"},
        {Direction::RIGHT, "\033[1;32m>\033[0m"},
        {Direction::DOWN, "\033[1;32mv\033[0m"},
        {Direction::LEFT, "\033[1;32m<\033[0m"}
    };

    Direction dir = Direction::UP;
    pair<int, int> curr = start;
    int n_steps = 0;
    while (n_steps <= max_steps && curr.first >= 0 && curr.first < n && curr.second >= 0 && curr.second < m) {
        curr = {curr.first + dir_map[dir].first, curr.second + dir_map[dir].second};
        if (curr.first >= 0 && curr.first < n && curr.second >= 0 && curr.second < m) {
            // Free space
            if (map[curr.first][curr.second] == ".") { 
                map[curr.first][curr.second] = dir_cursor[dir];
            }
            // Obstacle
            else if (map[curr.first][curr.second] == obstacle) {
                curr = {curr.first - dir_map[dir].first, curr.second - dir_map[dir].second};
                dir = static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
            }
            n_steps++;
        }
    }

    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[0].size(); j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
}

int part2(vector<vector<int>> map, const pair<int, int> start, const int n_steps) {
    int n = map.size(), m = map[0].size();
    enum class Direction { 
        UP, RIGHT, DOWN, LEFT 
    };
    unordered_map<Direction, pair<int, int>> dir_map = {
        {Direction::UP, {-1, 0}},
        {Direction::RIGHT, {0, 1}},
        {Direction::DOWN, {1, 0}},
        {Direction::LEFT, {0, -1}}
    };

    Direction dir = Direction::UP;
    pair<int, int> curr = start;
    vector<pair<int, int>> obstacles;
    vector<set<int>> obstacles_by_col(m);
    vector<set<int>> obstacles_by_row(n);
    vector<pair<int, int>> potential_obstacles;

    unordered_map<Direction, vector<pair<int, int>>> dir_paths = {
        {Direction::UP, {start}},
        {Direction::RIGHT, {}},
        {Direction::DOWN, {}},
        {Direction::LEFT, {}}
    };
    vector<tuple<int, int, Direction>> path({make_tuple(start.first, start.second, dir)});

    while (curr.first >= 0 && curr.first < n && curr.second >= 0 && curr.second < m) {
        curr = {curr.first + dir_map[dir].first, curr.second + dir_map[dir].second};
        if (curr.first >= 0 && curr.first < n && curr.second >= 0 && curr.second < m) {
            // Free space
            if (map[curr.first][curr.second] == 0) { 
                map[curr.first][curr.second] = 2; 
            }
            // Obstacle
            else if (map[curr.first][curr.second] == 1) {
                obstacles.push_back({curr.first, curr.second});
                obstacles_by_col[curr.second].insert(curr.first);
                obstacles_by_row[curr.first].insert(curr.second);
                curr = {curr.first - dir_map[dir].first, curr.second - dir_map[dir].second};
                dir = static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
                continue;
            }

            path.push_back(make_tuple(curr.first, curr.second, dir));
            dir_paths[dir].push_back(curr);

            if (dir == Direction::LEFT && curr.second == start.second-1) {
                potential_obstacles.push_back({curr.first, curr.second});
            }
        }
    }
    
    int n_obstacles = 0;
    unordered_map<int, unordered_set<int>> potential_obstacles_set;

    // Completing a square
    for (size_t i = 0; i < obstacles.size()-2; i++) {
        pair<int, int> obs1 = obstacles[i], obs3 = obstacles[i+2];
        Direction dir_obs3 = static_cast<Direction>((i+2) % 4);

        Direction dir_new_obs = static_cast<Direction>((static_cast<int>(dir_obs3) + 1) % 4);
        pair<int, int> new_obs = {0, 0};
        if (dir_new_obs == Direction::UP) { new_obs = {obs1.first-1, obs3.second+1}; }
        else if (dir_new_obs == Direction::RIGHT) { new_obs = {obs3.first+1, obs1.second+1}; }
        else if (dir_new_obs == Direction::DOWN) { new_obs = {obs1.first+1, obs3.second-1}; }
        else if (dir_new_obs == Direction::LEFT) { new_obs = {obs3.first-1, obs1.second-1}; }

        if (new_obs != start && new_obs.first >= 0 && new_obs.first < n && new_obs.second >= 0 && new_obs.second < m) {
            if (dir_new_obs == Direction::UP) { 
                bool valid = true;
                for (const auto& obs : obstacles_by_col[new_obs.second]) {
                    if (obs >= new_obs.first && obs <= obs3.first) {
                        valid = false;
                        break;
                    }
                }

                if (!valid) { continue; }
            }
            else if (dir_new_obs == Direction::RIGHT) { 
                bool valid = true;
                for (const auto& obs : obstacles_by_row[new_obs.first]) {
                    if (obs <= new_obs.second && obs >= obs3.second) {
                        valid = false;
                        break;
                    }
                }

                if (!valid) { continue; }
            }
            else if (dir_new_obs == Direction::DOWN) { 
                bool valid = true;
                for (const auto& obs : obstacles_by_col[new_obs.second]) {
                    if (obs <= new_obs.first && obs >= obs3.first) {
                        valid = false;
                        break;
                    }
                }

                if (!valid) { continue; }
            }
            else if (dir_new_obs == Direction::LEFT) { 
                bool valid = true;
                for (const auto& obs : obstacles_by_row[new_obs.first]) {
                    if (obs >= new_obs.second && obs <= obs3.second) {
                        valid = false;
                        break;
                    }
                }

                if (!valid) { continue; }
            }

            pair<int, int> obs2 = obstacles[i+1];
            vector<pair<int, int>> potential_square({obs1, obs2, obs3, new_obs}); 
            // vector temp_obs = obstacles;
            // temp_obs.push_back(new_obs);
            // simulate(temp_obs, start, n, m, 2*n_steps);

            // print_obstacles(obstacles, potential_square, start, n, m);
            // cout << endl;

            n_obstacles++;
            potential_obstacles_set[new_obs.first].insert(new_obs.second);
        }
    }

    // cout << "Potential obstacles" << endl;
    for (const auto& new_obs : potential_obstacles) {
        auto it = std::upper_bound(obstacles_by_col[new_obs.second+1].begin(), obstacles_by_col[new_obs.second+1].end(), start.first);
        if (it == obstacles_by_col[new_obs.second+1].end() || *it > new_obs.first) { 
            if (potential_obstacles_set.contains(new_obs.first) && !potential_obstacles_set[new_obs.first].contains(new_obs.second)) { 
                n_obstacles++; 
                potential_obstacles_set[new_obs.first].insert(new_obs.second);

                // vector<pair<int, int>> potential_square({new_obs}); 
                // print_obstacles(obstacles, potential_square, start, n, m);
                // cout << endl;
            }
        }
    }
    // Forcing a return to the start
    return n_obstacles;
}

int main(int argc, char** argv) {
    string filename = argv[1];

    auto [map, start] = parse(filename);

    // for (size_t i = 0; i < map.size(); i++) {
    //     for (size_t j = 0; j < map[0].size(); j++) {
    //         cout << map[i][j] << ", ";
    //     }
    //     cout << endl;
    // }

    auto [part1_ans, n_steps] = part1(map, start);
    int part2_ans = part2(map, start, n_steps);
    cout << "[Part 1]: " << part1_ans << endl;
    cout << "[Part 2]: " << part2_ans << endl;
    return 0;
}