// main file to run program

#include <iostream>
#include <string>

using namespace std;

int main() {
    cout << "You have entered into the Eight Puzzle solver." << endl;
    cout << "You can either use a pre-built puzzle or enter your own. Type 1 for a pre-built puzzle, or 2 to enter your own!" << endl;
    int selection;

    cin >> selection;

    cout << "Choose which search algorighm you would like to use: " << endl;
    cout << "1) Uniform Cost Search" << endl;
    cout << "2) A* with Misplaced Tile heuristic" << endl;
    cout << "3) A* with Euclidean Distance heuristic" << endl;
    
    int algorithm_selection;
    cin >> algorithm_selection;

    if(algorithm_selection == 1) {
        cout << "Uniform Cost Search selected." << endl;
    } else if (algorithm_selection == 2) {
        cout << "A* with Misplaced Tile heuristic selected." << endl;
    } else if (algorithm_selection == 3) {
        cout << "A* with Euclidean Distance heuristic selected" << endl;
    } else {
        cout << "Invalid Selection, you can only select 1-3" << endl;
        return 0;
    }
    


    
    







    
}