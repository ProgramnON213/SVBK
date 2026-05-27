#include "Algo.h" // Assuming your function is declared here

void printPath(PathNode* head);
void testTask1();
void testTask2();
void testTask3();

int main() {
    testTask3();

    return 0;
}

void testTask1() {
    double adjMatrix[100][100] = {0};
    adjMatrix[0][1] = 1;
    adjMatrix[1][3] = 1;
    adjMatrix[1][5] = 1;
    adjMatrix[3][2] = 1;
    adjMatrix[3][5] = 1;
    adjMatrix[2][4] = 1;
    adjMatrix[4][6] = 1;
    adjMatrix[5][6] = 1;

    PathNode* path = findSocialPath(adjMatrix, 0, 6);
    printPath(path);
    delete path;
}

void testTask2() {
    double weightMatrix[100][100] = {0};
    
    // Outer Path 1 (Top)
    weightMatrix[0][6] = weightMatrix[6][0] = 10.0;
    weightMatrix[6][7] = weightMatrix[7][6] = 10.1;
    
    // Outer Path 2 (Bottom)
    weightMatrix[0][1] = weightMatrix[1][0] = 9.0;
    weightMatrix[1][7] = weightMatrix[7][1] = 11.4;
    
    // Complex Middle Paths
    weightMatrix[0][3] = weightMatrix[3][0] = 5.4;
    weightMatrix[1][4] = weightMatrix[4][1] = 4.6;
    weightMatrix[1][5] = weightMatrix[5][1] = 6.8;
    weightMatrix[2][6] = weightMatrix[6][2] = 5.5;
    weightMatrix[2][3] = weightMatrix[3][2] = 5.3;
    weightMatrix[2][4] = weightMatrix[4][2] = 5.7;
    weightMatrix[3][4] = weightMatrix[4][3] = 6.3;
    weightMatrix[4][5] = weightMatrix[5][4] = 2.9;
    weightMatrix[5][7] = weightMatrix[7][5] = 4.9;

    int coords[100][2] = {
        {0, 0}, {9, 0}, {4, 7}, {3, 2}, {8, 4}, {9, 6}, {0, 10}, {10, 10}
    };

    PathNode* path1 = findDronePath(weightMatrix, coords, 0, 7, 1);
    PathNode* path2 = findDronePath(weightMatrix, coords, 0, 7, 2);
    PathNode* path3 = findDronePath(weightMatrix, coords, 0, 7, 3);

    printPath(path1);
    printPath(path2);
    printPath(path3);

    delete path1;
    delete path2;
    delete path3;
}

void testTask3() {
    int m = 4;      int n = 4;
    int startX = 0; int startY = 0;
    int goalX = 3;  int goalY = 3;

    vector<vector<int>> visualGrid = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    int warehouse[100][100] = {0};
    int ROWS = visualGrid.size();
    int COLS = visualGrid[0].size();

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            warehouse[y][x] = visualGrid[y][x];
        }
    }



    PathNode* path1 = findWarehousePath(warehouse, m, n, startX, startY, goalX, goalY, 1);
    PathNode* path2 = findWarehousePath(warehouse, m, n, startX, startY, goalX, goalY, 2);
    printPath(path1);
    printPath(path2);
    delete path1;
    delete path2;
}

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
