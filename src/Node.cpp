#include "Node.h"
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <string>
using namespace std;

Node::Node(const vector<vector<int>>&gridState,
            int pathCost, //path cost from start node aka moves so far
            int heuristicCost, //heuristic estimate to goal
            Node* parentNode,
            const Position& blankTile,
            const string& moveUsed): 
    grid(gridState),        //the board
    gValue(pathCost),  //g(n): cost to reach this node
    hValue(heuristicCost),  //h(n): heuristic estimate to the goal
    moveMade(moveUsed), 
    parent(parentNode), //back-pointer pointing to parent 
    blankPos(blankTile) {} //location of blank tile using row, col

const vector<vector<int>>& Node::get_state() const
{
    return grid;
}

int Node::get_path_cost() const
{
    return gValue;
}

int Node::get_heuristic() const
{
    return hValue;
}

int Node::get_total_cost() const
{
    int total = gValue + hValue;
    return total;
}

bool Node::is_goal(const vector<vector<int>>&goal) const
{
    return grid == goal;
}

void Node::set_heuristic(int h) 
{ 
    hValue = h; 
}

//Expand the current node by making possible moves
//moves is list of actions like UP, DOWN, LEFT, RIGHT
vector<Node*> Node::add_child(const vector<string>& moves)
{
    //this vector 'children' stores all the newly created child nodes
    vector<Node*> children;
    //these store where the blak tile currently is
    int blankRow = blankPos.row;
    int blankCol = blankPos.col;

    
    //go through each move (UP, DOWN, LEFT, RIGHT)
    for (const string& move : moves) {
        //these are possible positions that will be adjusted based on 'move'
        int newRow = blankRow;
        int newCol = blankCol;

        //following moves (UP, DOWN, LEFT, RIGHT) adjust newRow and newCol
        if (move == "UP")       
        {
            newRow--;
        }
        else if (move == "DOWN") 
        {
            newRow++;
        }
        else if (move == "LEFT") 
        {
            newCol--;
        }
        else if (move == "RIGHT") 
        {
            newCol++;
        }
        else //if string is not one of the four valid moves, then skip aka unknown label          
        {
            continue;
        }  

        //bounds check = validate that destination is inside grid; If outside, then the move is skipped
        bool outOfBounds = (newRow < 0 || newRow >= grid.size() || newCol < 0 || newCol >= grid[0].size());
        if (outOfBounds == true) 
        {
            continue;
        }

        //makes a copy of the current board so we can modify it for the child
        vector<vector<int>> nextGrid = grid;
        //swaps blank tile and tile at the destination
        swap(nextGrid[blankRow][blankCol], nextGrid[newRow][newCol]);

        //create child node (g = g+1, h = 0 here)
        //gValue + 1: path cost increases by 1
        //heuristic set to 0
        //this = parent pointer is the current node
        //{newRow, newCol} = new updated blank position
        //move = nots the move that made this child
        Position newBlankPos = {newRow, newCol};
        Node* child = new Node(nextGrid, gValue + 1, 0, this, newBlankPos, move);
        
        //stores child in 'children' vector
        children.push_back(child);
        }
    
    return children;
}
