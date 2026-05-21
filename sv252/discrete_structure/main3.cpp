#include "Algo.h"

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
    int warehouse[100][100] = {0}; // Clear the grid completely

    cout << "=========================================" << endl;
    cout << "RUNNING TASK 3 DIAGNOSTIC PATH TESTS" << endl;
    cout << "=========================================" << endl << endl;

    // ---------------------------------------------------------
    // TEST CASE 1: Cardinal Movement Only (Straight line right)
    // ---------------------------------------------------------
    cout << "--- Test Case 1: Straight Cardinal Path (No Obstacles) ---" << endl;
    PathNode* path1 = findWarehousePath(warehouse, 3, 3, 0, 0, 0, 2, 1);
    printPath(path1);
    delete path1;
    cout << endl;

    // ---------------------------------------------------------
    // TEST CASE 2: Diagonal Movement Only (Perfect Corner diagonal)
    // ---------------------------------------------------------
    cout << "--- Test Case 2: Pure Diagonal Path (No Obstacles) ---" << endl;
    PathNode* path2 = findWarehousePath(warehouse, 3, 3, 0, 0, 2, 2, 2);
    printPath(path2);
    delete path2;
    cout << endl;

    // ---------------------------------------------------------
    // TEST CASE 3: Wall Obstacle Detour Handling
    // ---------------------------------------------------------
    cout << "--- Test Case 3: Navigating Around a Wall ---" << endl;
    warehouse[0][1] = 1; // Construct a wall hurdle
    warehouse[1][1] = 1;
    
    PathNode* path3 = findWarehousePath(warehouse, 3, 3, 0, 0, 0, 2, 2);
    printPath(path3);
    delete path3;
    cout << "=========================================" << endl;

    return 0;
}