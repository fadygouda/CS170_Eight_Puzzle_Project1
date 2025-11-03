#include "The_Problem.h"
#include <queue>
#include <iostream>
#include <cmath>
#include <unordered_set>

using namespace std;

string The_Problem::state_to_string(const vector<vector<int>>& state) const {
    string hash;
    for (const auto& row : state) {
        for (int tile : row) {
            hash += to_string(tile) + ",";
        }
    }
    return hash;
}

double The_Problem::heuristic_misplaced_tiles(const vector<vector<int>>& state) const {
    int misplaced_tiles = 0;
    for (unsigned i = 0; i < state.size(); ++i) {
        for (unsigned j = 0; j < state[i].size(); ++j) {
            if (state[i][j] != 0 && state[i][j] != goal[i][j]) {
                ++misplaced_tiles;
            }
        }
    }
    return misplaced_tiles;
}

double The_Problem::heuristic_euclidean_distance(const vector<vector<int>>& state) const {
    double distance = 0.0;
    int dim = state.size();

    for (int i = 0; i < state.size(); ++i) {
        for (unsigned j = 0; j < state[i].size(); ++j) {
            int tile = state[i][j]; 
            if (tile != 0) {
                int target_x = (tile - 1) / dim;
                int target_y = (tile - 1) % dim;

                distance += std::sqrt((i - target_x) * (i - target_x) + (j - target_y) * (j - target_y));
            }
        }
    }
    return distance;
}

struct CompareNode {
    bool operator()(const Node* a, const Node* b) const {
        return (a->get_total_cost() > b->get_total_cost());
    }
};

Node* The_Problem::a_star_search(double (The_Problem::*heuristic)(const vector<vector<int>>& state) const){

    priority_queue<Node*, vector<Node*>, CompareNode> frontier;
    unordered_set<string> explored;
    unordered_map<string, int> frontier_map;

    Node::Position blank_pos = {-1, -1};

    for (int i = 0; i < initial.size(); ++i) {
        for (int j = 0; j < initial[i].size(); ++j) {
            if (initial[i][j] == 0) {
                blank_pos = {i, j};
                break;
            }
        }
        if (blank_pos.row != -1) break;
    }

    int initial_h = heuristic ? (this->*heuristic)(initial) : 0;
    Node* start = new Node(initial, 0, initial_h, nullptr, blank_pos, "");
    frontier.push(start);
    frontier_map[state_to_string(initial)] = start->get_total_cost();

    cout << "Initial heuristic: " << initial_h << endl;

    int nodes_expanded = 0, max_queue_size = 0;

    while (!frontier.empty()) {
        Node* current = frontier.top();
        frontier.pop();
        frontier_map.erase(state_to_string(current->get_state()));

        ++nodes_expanded;
        max_queue_size = max(max_queue_size, (int)frontier.size());

        cout << "Expanding state:\n";
        display_puzzle(current->get_state());
        cout << "g(n) = " << current->get_path_cost()
            << ", h(n) = " << current->get_heuristic()
            << ", f(n) = " << current->get_total_cost() << "\n\n";

        if (current->is_goal(goal)) {
            cout << "Goal!!!\n"
                << "Total nodes expanded: " << nodes_expanded << "\n"
                << "Maximum queue size at any one time: " << max_queue_size << "\n"
                << "Depth of the goal node was: " << current->get_path_cost() << endl;
            return current;
        }
    }
}

void The_Problem::display_puzzle(const vector<vector<int>>& state) const {
    for (const auto& row : state) {
        for (int num : row) {
            if (num == 0) {
                cout << "* ";
            } else {
                cout << num << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}