#include "Algo.h"

// Return the index in list of person with lowest F
int findLowestFIndex(vector<PathNode*> list) {
    double lowestF = list[0]->f;
    int idx = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list[i]->f < lowestF) {
            lowestF = list[i]->f;
            idx = i;
        }
    }
    return idx;
}

double* setupHCost1(double adjMatrix[100][100], int start) {
    double* hCosts = new double[100];
    fill_n(hCosts, 100, -1.0);
    int queue[100];
    int head = 0;
    int tail = 0;
    queue[head] = start;
    hCosts[start] = 0;
    tail++;

    while (head != tail) {
        int idx = queue[head];
        for (int i = 0; i < 100; i++) {
            if (adjMatrix[i][idx] > 0 && hCosts[i] == -1.0) {
                queue[tail] = i;
                tail++;

                hCosts[i] = hCosts[idx] + 1.0;
            }
        }
        head++;
    }

    return hCosts;
}

PathNode* findSocialPath(double adjMatrix[100][100], int startPerson, int goalPerson) {
    // Implementation goes here
    vector<PathNode*> openList;
    bool visited[100] = {false};    // have we visited this node
    int parent[100] = {-1};     // the index node comes from the data node
    fill_n(parent, 100, -1);
    double gCosts[100] = {INFINITY};
    fill_n(gCosts, 100, INFINITY);
    gCosts[startPerson] = 0.0;
    double* hCosts = setupHCost1(adjMatrix, goalPerson);

    PathNode* startNode = new PathNode(to_string(startPerson), 0, hCosts[startPerson]);
    openList.push_back(startNode);

    while (!openList.empty()) {
        int curIndex = findLowestFIndex(openList);
        PathNode* curNode = openList[curIndex];
        openList.erase(openList.begin() + curIndex);

        int curPerson = stoi(curNode->name);
        delete curNode;

        if (curPerson == goalPerson) {
            break;
        }

        visited[curPerson] = true;
        for (int i = 0; i < 100; i++) {
            if (adjMatrix[curPerson][i] > 0 && !visited[i]) {
                double newG = gCosts[curPerson] + 1;
                if (newG < gCosts[i]) {
                    gCosts[i] = newG;
                    parent[i] = curPerson;
                    PathNode* tempNode = new PathNode(to_string(i), gCosts[i], hCosts[i]);
                    openList.push_back(tempNode);
                }
            }
        }
    }

    if (parent[goalPerson] == -1 && startPerson != goalPerson) {
        for (int i = 0; i < openList.size(); i++) {
            delete openList[i];
        }
        openList.clear();
        delete[] hCosts;
        
        return nullptr;
    }

    int backtrackPerson = goalPerson;
    PathNode* head = nullptr;
    while (backtrackPerson != startPerson) {
        PathNode* node = new PathNode(to_string(backtrackPerson), gCosts[backtrackPerson], hCosts[backtrackPerson]);
        head = addNodeToStart(head, node);
        backtrackPerson = parent[backtrackPerson];
    }
    PathNode* node = new PathNode(to_string(backtrackPerson), gCosts[backtrackPerson], hCosts[backtrackPerson]);
    head = addNodeToStart(head, node);

    for (int i = 0; i < openList.size(); i++) {
        delete openList[i];
    }
    openList.clear();
    delete[] hCosts;

    return head;
}

string convertCoordToStr(int coord[2]) {
    return "(" + to_string(coord[0]) + "," + to_string(coord[1]) + ")";
}


/*
– Mode 1: Manhattan distance — |x1 − x2| + |y1 − y2|
– Mode 2: Euclidean distance — sqrt((x1 − x2)^2 + (y1 − y2)^2)
– Mode 3: Chebyshev distance — max(|x1 − x2|, |y1 − y2|)
*/
double calculateH(int x1, int y1, int x2, int y2, int mode) {
    // TODO
    if (mode == 1) {
        return abs(x1 - x2) + abs(y1 - y2);
    }
    else if (mode == 2) {
        return sqrt(pow((x1-x2), 2) + pow((y1-y2), 2));
    }
    else if (mode == 3) {
        return max(abs(x1-x2), abs(y1-y2));
    }
    return -1;
}

PathNode* findDronePath(double weightMatrix[100][100], int coords[100][2], int startPoint, int goalPoint, int mode) {
    // Implementation goes here
    vector<PathNode*> openList;
    bool visited[100] = {false};    // have we visited this node
    int parent[100] = {-1};     // the index node comes from the data node
    fill_n(parent, 100, -1);
    double gCosts[100] = {INFINITY};
    fill_n(gCosts, 100, INFINITY);
    gCosts[startPoint] = 0.0;
    int goalX = coords[goalPoint][0];
    int goalY = coords[goalPoint][1];

    PathNode* startNode = new PathNode(to_string(startPoint), gCosts[startPoint], 
    calculateH(coords[startPoint][0], coords[startPoint][1], goalX, goalY, mode));

    openList.push_back(startNode);

    while (!openList.empty()) {
        int curIndex = findLowestFIndex(openList);
        PathNode* curNode = openList[curIndex];
        openList.erase(openList.begin() + curIndex);

        int curPoint = stoi(curNode->name);
        delete curNode;

        if (curPoint == goalPoint) {
            break;
        }

        visited[curPoint] = true;
        for (int i = 0; i < 100; i++) {
            if (weightMatrix[curPoint][i] > 0 && !visited[i]) {
                double newG = gCosts[curPoint] + weightMatrix[curPoint][i];
                if (newG < gCosts[i]) {
                    gCosts[i] = newG;
                    parent[i] = curPoint;
                    double h = calculateH(coords[i][0], coords[i][1], goalX, goalY, mode);
                    PathNode* tempNode = new PathNode(to_string(i), gCosts[i], h);
                    openList.push_back(tempNode);
                }
            }
        }
    }

    int backtrackPoint = goalPoint;
    PathNode* head = nullptr;
    while (backtrackPoint != startPoint) {
        double h = calculateH(coords[backtrackPoint][0], coords[backtrackPoint][1], goalX, goalY, mode);
        PathNode* node = new PathNode(convertCoordToStr(coords[backtrackPoint]), gCosts[backtrackPoint], h);
        head = addNodeToStart(head, node);
        backtrackPoint = parent[backtrackPoint];
    }
    double h = calculateH(coords[backtrackPoint][0], coords[backtrackPoint][1], goalX, goalY, mode);
    PathNode* node = new PathNode(convertCoordToStr(coords[backtrackPoint]), gCosts[backtrackPoint], h);
    head = addNodeToStart(head, node);

    for (int i = 0; i < openList.size(); i++) {
        delete openList[i];
    }
    openList.clear();

    return head;
}
