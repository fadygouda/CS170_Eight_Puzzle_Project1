#pragma once
#include <vector>
#include <string>
#include "Node.h"

using namespace std;

class The_Problem {
public:
    The_Problem(const vector<vector<int>>& initial, const vector<vector<int>>& goal);

    const vector<vector<int>>& get_initial() const;
    const vector<vector<int>>& get_goal() const;

    double heuristic_misplaced_tiles(const vector<vector<int>>& state) const;
    double heuristic_euclidean_distance(const vector<vector<int>>& state) const;

    void display_puzzle(const vector<vector<int>>& state) const;

    Node* euclidean_distance_a_star();
    Node* uniform_cost_search();
    Node* misplaced_tile_a_star();

private:
    vector<vector<int>> initial;
    vector<vector<int>> goal;

    // struct Position {
    //     int row;
    //     int column;
    // };

    Node* a_star_search(double (The_Problem::*heuristic)(const vector<vector<int>>& state) const);
    string state_to_string(const vector<vector<int>>& state) const;
    // Position find_empty() const;
};
