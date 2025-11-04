// main file to run program
#include "../headers/The_Problem.h"
#include "../headers/Problem.h/Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>



using namespace std;

void create_puzzle(vector<vector<int>> & initial_state) {
    std::cout << "You are now creating a puzzle, enter it here. Please use a '*' to represent a blank node. Also, enter spaces between numbers." << endl;

    for (int i=0; i<3; i++) {
        std::cout << "Enter row # " << i+1 << endl;
        for (int j=0; j<3; j++) {
            string user_inserted_value;
            std::cin >> user_inserted_value;

            if (user_inserted_value == "*") {
                initial_state[i][j] = 0;
            } else {
                initial_state[i][j] = stoi(user_inserted_value);
            }
        }
    }
}

void print_results(Node* target) {
    if(!target) {
        std::cout << "No results generated.\n";
        return;
    }

    std::cout << "Results were generated in " << target->get_path_cost() << " steps:\n";

    std::stack<const Node*> path;
    for (const Node* cur = target; cur != nullptr; cur = cur->get_parent()) {
        path.push(cur);
    }

    if(!path.empty()) path.pop();

    bool first = true;
    while (!path.empty()) {
        const Node* cur = path.top();
        path.pop();
        if (!first) std::cout << ' ';
        first = false;
        std::cout << cur->get_move();
    }
    std::cout << '\n';
}

int main() {
    std::cout << "You have entered into the Eight Puzzle solver." << endl;
    std::cout << "You can either use a pre-built puzzle or enter your own. Type 1 for a pre-built puzzle, or 2 to enter your own!" << endl;
    int selection;

    std::cin >> selection;


    const vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    vector<vector<int>> initial(3, vector<int>(3));

    if (selection == 1) {
        initial = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
        };
        std::cout << "Using pre-built puzzle:\n";
    } else if (selection == 2) {
        create_puzzle(initial);
        std::cout << "Custom puzzle \n";
    } else {
        std::cout << "Invalid selection, Exiting.\n";
        return 0;
    }

    std::cout << "Choose which search algorighm you would like to use: " << endl;
    std::cout << "1) Uniform Cost Search" << endl;
    std::cout << "2) A* with Misplaced Tile heuristic" << endl;
    std::cout << "3) A* with Euclidean Distance heuristic" << endl;
    
    int algorithm_selection;
    std::cin >> algorithm_selection;

    The_Problem problem(initial, goal);
    std::cout << "Initial puzzle:\n";
    problem.display_puzzle(problem.get_initial());

  
    Node*target = nullptr;


    if(algorithm_selection == 1) {
        std::cout << "Uniform Cost Search selected." << endl;
        target = problem.uniform_cost_search();
    } else if (algorithm_selection == 2) {
        std::cout << "A* with Misplaced Tile heuristic selected." << endl;
        target = problem.misplaced_tile_a_star();
    } else if (algorithm_selection == 3) {
        std::cout << "A* with Euclidean Distance heuristic selected" << endl;
        target = problem.euclidean_distance_a_star();
    } else {
        std::cout << "Invalid Selection, you can only select 1-3" << endl;
        return 0;
    }
    
    print_results(target);

    return 0;
}