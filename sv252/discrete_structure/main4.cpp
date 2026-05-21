#include "Algo.h"

// --- [INSERT YOUR HELPER FUNCTIONS HERE] ---
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
    // 1. Initialize a full 100x100 grid to 0
    int floorPlan[100][100] = {0}; 
    
    int m = 5; // Rows
    int n = 5; // Columns

    // 2. Build a wall to test pathing
    // This blocks a direct diagonal path from (0,0) to (4,4)
    floorPlan[1][2] = 1;
    floorPlan[2][2] = 1;
    floorPlan[3][2] = 1;

    double weightMatrix[100][100];
    int mode = 2; // Will map to 3 (Chebyshev) inside your function

    // Start at Top-Left (0,0), Target Bottom-Right (4,4)
    PathNode* path = findEvacuationRoute(floorPlan, m, n, 0, 0, 4, 4, weightMatrix, mode);

    // 3. Print the results
    cout << "--- Evacuation Path ---" << endl;
    printPath(path);

    // 4. Memory cleanup for the printed path
    delete path;

    return 0;
}