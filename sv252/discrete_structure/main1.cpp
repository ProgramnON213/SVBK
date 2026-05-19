#include "Algo.h"

using namespace std;

// The official LMS print function for local testing
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
    // 1. Initialize a 100x100 matrix with 0.0 (no connections)
    double adjMatrix[100][100] = {0.0};

    // 2. Build a simple test social network
    // Person 0 connects to Person 1 and Person 2
    adjMatrix[0][1] = 1.0; 
    adjMatrix[1][0] = 1.0;
    adjMatrix[0][2] = 1.0;
    adjMatrix[2][0] = 1.0;
    
    // Person 1 connects to Person 3
    adjMatrix[1][3] = 1.0;
    adjMatrix[3][1] = 1.0;
    
    // Person 2 connects to Person 4
    adjMatrix[2][4] = 1.0;
    adjMatrix[4][2] = 1.0;
    
    // Person 3 connects to Person 5 (Goal)
    adjMatrix[3][5] = 1.0;
    adjMatrix[5][3] = 1.0;
    
    // Person 4 connects to Person 5 (Goal)
    adjMatrix[4][5] = 1.0;
    adjMatrix[5][4] = 1.0;

    // In this network, both paths (0 -> 1 -> 3 -> 5) and (0 -> 2 -> 4 -> 5) 
    // are exactly 3 steps. Let's see which one I find!

    int startPerson = 0;
    int goalPerson = 5;

    cout << "Running A* for Task 1..." << endl;
    
    // 3. Run the algorithm
    PathNode* resultHead = findSocialPath(adjMatrix, startPerson, goalPerson);

    // 4. Print the results
    if (resultHead != nullptr) {
        printPath(resultHead);
    } else {
        cout << "No path found!" << endl;
    }

    // 5. Clean up memory
    delete resultHead;

    return 0;
}