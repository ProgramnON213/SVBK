// main.cpp
#include <iostream>
#include <string>
#include "PathNode.h" // Make sure you have PathNode.h properly defined

using namespace std;

// Placed here ONLY for local testing. Do not submit this to the LMS!
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
    cout << "--- Testing PathNode Linking ---" << endl;

    PathNode* myPath = nullptr; // Start with an empty list

    // 1. Simulate finding the Goal node first (working backwards)
    PathNode* goalNode = new PathNode("Goal(5,5)", 10.0, 0.0);
    myPath = addNodeToStart(myPath, goalNode);

    // 2. Add an intermediate node
    PathNode* middleNode = new PathNode("Up-Right", 8.5, 1.5);
    myPath = addNodeToStart(myPath, middleNode);

    // 3. Add another intermediate node
    PathNode* middleNode2 = new PathNode("Up", 7.0, 3.0);
    myPath = addNodeToStart(myPath, middleNode2);

    // 4. Add the Start node
    PathNode* startNode = new PathNode("Start(0,0)", 0.0, 10.0);
    myPath = addNodeToStart(myPath, startNode);

    // 5. Print the path to verify order (Start -> Up -> Up-Right -> Goal)
    printPath(myPath);

    // 6. Clean up memory to prevent leaks
    // Thanks to our cascading destructor, deleting the head deletes the whole list!
    delete myPath; 
    
    cout << "Memory successfully cleared. Ready for the next task!" << endl;

    return 0;
}
