#include <iostream>
#include <vector>
#include "Algo.h" // Assuming your function is declared here

using namespace std;

// The printPath function required for local testing [cite: 491, 492]
void printPath(PathNode* head) {
    cout << "Solution Path:\n";
    while (head != nullptr) {
        cout << "Node: " << head->name 
             << " | f: " << head->f 
             << " | g: " << head->g 
             << " | h: " << head->h << "\n";
        head = head->next;
    }
}

int main() {
    // 1. Initialize empty matrices
    double weightMatrix[100][100] = {0.0};
    int coords[100][2] = {0};

    // 2. Set up Coordinates for 4 points
    coords[0][0] = 0;  coords[0][1] = 0;   // Start Point
    coords[1][0] = 0;  coords[1][1] = 10;  // Detour Point
    coords[2][0] = 10; coords[2][1] = 10;  // Goal Point
    coords[3][0] = 5;  coords[3][1] = 5;   // Shortcut Point

    // 3. Set up Weights (Distances between points)
    // Path A: 0 -> 1 -> 2 (Total cost: 20)
    weightMatrix[0][1] = 10.0;
    weightMatrix[1][2] = 10.0;
    
    // Path B: 0 -> 3 -> 2 (Total cost: ~14.14 - The Optimal Path)
    weightMatrix[0][3] = 7.07;
    weightMatrix[3][2] = 7.07;

    int startPoint = 0;
    int goalPoint = 2;

    // 4. Test Mode 1 (Manhattan)
    cout << "--- Testing Mode 1: Manhattan ---" << endl;
    PathNode* path1 = findDronePath(weightMatrix, coords, startPoint, goalPoint, 1);
    if (path1 != nullptr) printPath(path1);
    
    delete path1;

    return 0;
}