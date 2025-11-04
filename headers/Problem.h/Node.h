#pragma once

#include <vector>
#include <string>
#include <utility>
using namespace std;

class Node {
public:
    //Struct to represent the blank position.
    struct Position {
        int row;
        int col;
    };

    //Node(const vector<vector<int>>& game_state, int path_cost, int heuristicCost, Node* parent, const Position& blank_position, const string& chosen_action) : state(game_state), path_cost(path_cost), heuristic(heuristicCost), parent(parent), blank_pos(blank_position), action(chosen_action), depth(0) {} 

    const Node* get_parent() const {return parent;}
    const std::string& get_move() const {return moveMade;}
    const Position& get_blank_pos() const {return blankPos;}

    
    Node (const vector<vector<int>>& gridState,
    int pathCost,
    int heuristicCost,
    Node* parentNode,
    const Position& blankTile,
    const string& moveUsed);

    //this will return true if the current board is the goal board
    bool is_goal(const vector<vector<int>>& goalState) const;
    //getter for g cost
    int get_path_cost() const;
    //getter for h cost
    int get_heuristic() const;
    //f = g+h
    int get_total_cost() const;
    //getting the state
    const vector<vector<int>>& get_state() const;
    vector<Node*> add_child(const vector<string>& moves);
    
    void set_heuristic(int h);



private:
    vector<vector<int>> grid;//Layout of the puzzle
    int gValue;              //Cost from the start
    int hValue;              //Heuristic value
    int depth = 0;           
    string moveMade;         //Moved used to reach node    
    Node* parent;            //Pointer to parent
    Position blankPos; //Blank tile coords (row, column)
};
