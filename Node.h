#pragma once

#include <vector>
#include <string>
using namespace std;

class Node {
public:
    // Struct to represent the blank position.
    struct Position {
        int row;
        int col;
    };

    Node(const vector<vector<int>>& game_state, int path_cost, int heuristicCost, Node* parent, const Position& blank_position, const string& chosen_action) : state(game_state), path_cost(path_cost), heuristic(heuristicCost), parent(parent), blank_pos(blank_position), action(chosen_action), depth(0) {} 

    bool is_goal(const vector<vector<int>>& goal) const {
        return state == goal;
    }

    int get_heuristic() const;
    int get_total_cost() const;
    const vector<vector<int>>& get_state() const;

    vector<Node*> add_child(const vector<string>& actions);

private:
    vector<vector<int>> state;
    int path_cost;          
    int heuristic;        
    int depth;          
    string action;          
    Node* parent;        
    Position blank_pos;       
};
