#include "Algo.h"

// Return the index in list of person with lowest F, if F is equal, return with lowest H
int findLowestFIndex(vector<PathNode*> list) {
    double lowestF = list[0]->f;
    int idx = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list[i]->f < lowestF) {
            lowestF = list[i]->f;
            idx = i;
        }
        else if (list[i]->f == lowestF && list[i]->h < list[idx]->h) {
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
string convertCoordToStr(int a, int b) {
    return "(" + to_string(a) + ", " + to_string(b) + ")";
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

PathNode* findDronePath(double weightMatrix[100][100], int coords[100][2], int startPoint, 
    int goalPoint, int mode) {
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



int convertCordToId(int r, int c, int numCol) {
    return r*numCol + c;
}

string getName(int childR, int childC, int parR, int parC) {
    string res = "";
    string seperator = "-";
    if (parR > childR) {res += "Up";}
    else if (parR < childR) {res += "Down";}
    if (childC != parC && childR != parR) {res += seperator;}
    if (parC > childC) {res += "Left";}
    else if (parC < childC) {res += "Right";}
    return res;
}

PathNode* findWarehousePath(int warehouse[100][100], int m, int n, int startX,
    int startY, int goalX, int goalY, int mode) {
    // Implementation goes here
    if (mode == 2) {mode = 3;}
    int dr[] = {-1, 0, 1, 0, -1, 1, 1, -1};
    int dc[] = {0, 1, 0, -1, 1, 1, -1, -1};
    int startR = startX;
    int startC = startY;
    int goalR = goalX;
    int goalC = goalY;

    vector<PathNode*> openList;
    bool visited[100*100] = {false};    // have we visited this node
    int parentX[100*100] = {-1};     // the index node comes from the data node
    int parentY[100*100] = {-1};
    double gCosts[100*100] = {INFINITY};

    fill_n(parentX, m*n, -1);
    fill_n(parentY, m*n, -1);
    fill_n(gCosts, m*n, INFINITY);
    gCosts[convertCordToId(startR, startC, n)] = 0.0;

    int startID = convertCordToId(startR, startC, n);
    PathNode* startNode = new PathNode(to_string(startID), gCosts[startID], calculateH(startR, startC, goalR, goalC, mode));

    openList.push_back(startNode);

    while (!openList.empty()) {
        int curIndex = findLowestFIndex(openList);
        PathNode* curNode = openList[curIndex];
        openList.erase(openList.begin() + curIndex);

        int id = stoi(curNode->name);
        int curR = id / n;
        int curC = id % n;
        delete curNode;

        if (curR == goalR && curC == goalC) {break;}

        visited[id] = true;
        
       for (int i = 0; i < 8; i++) {
        int neighborR = curR + dr[i];
        int neighborC = curC + dc[i];

        if (neighborC < 0 || neighborR < 0 || neighborC >= n || neighborR >= m) {continue;}
        if (warehouse[neighborR][neighborC] == 1) {continue;}
        if (visited[convertCordToId(neighborR, neighborC, n)] == 1) {continue;}

        int neighborID = convertCordToId(neighborR, neighborC, n);
        double newG = gCosts[id];
        if (i < 4) {newG += 1;} else {newG += 1.5;}
        if (newG < gCosts[neighborID]) {
            gCosts[neighborID] = newG;
            parentX[neighborID] = curR;
            parentY[neighborID] = curC;
            double h = calculateH(neighborR, neighborC, goalR, goalC, mode);
            PathNode* tempNode = new PathNode(to_string(neighborID), gCosts[neighborID], h);
            openList.push_back(tempNode);
        }
       }
    }

    int backR = goalR;
    int backC = goalC;
    PathNode* head = nullptr;
    while (!(backR == startR && backC == startC)) {
        int backID = convertCordToId(backR, backC, n);
        double h = calculateH(backR, backC, goalR, goalC, mode);
        string name = getName(backR, backC, parentX[backID], parentY[backID]);
        PathNode* node = new PathNode(name, gCosts[backID], h);
        head = addNodeToStart(head, node);
        backR = parentX[backID];
        backC = parentY[backID];
    }

    for (int i = 0; i < openList.size(); i++) {
        delete openList[i];
    }
    openList.clear();

    return head;
}


PathNode* findEvacuationPath(int floorPlan[100][100], int m, int n, 
    int startX, int startY, int exitX, int exitY, double weightMatrix[100][100], int mode) {
        // Scanning the floor
        if (mode == 2) {mode = 3;}
        int startR = startX;
        int startC = startY;
        int exitR = exitX;
        int exitC = exitY;

        fill_n(&weightMatrix[0][0], 100*100, 0.0);
        int dr[] = {-1, 0, 1, 0, -1, 1, 1, -1};
        int dc[] = {0, 1, 0, -1, 1, 1, -1, -1};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (floorPlan[i][j] == 0) {
                    for (int k = 0; k < 8; k++) {
                        int neighborR = i + dr[k];
                        int neighborC = j + dc[k];

                        if (neighborR < 0 || neighborC < 0 || neighborR >= m || neighborC >= n) {continue;}
                        if (floorPlan[neighborR][neighborC] == 0) {
                            int parID = convertCordToId(i, j, n);
                            int childID = convertCordToId(neighborR, neighborC, n);
                            double cost;
                            if (k < 4) {cost = 1;} else {cost = 1.5;}
                            weightMatrix[parID][childID] = cost;
                        }
                    }
                }
            }
        }

        vector<PathNode*> openList;
        double gCosts[100] = {0.0};
        int parent[100] = {-1};
        bool visited[100] = {false};

        fill_n(gCosts, 100, INFINITY);
        fill_n(parent, 100, -1);

        int startID = convertCordToId(startR, startC, n);
        gCosts[startID] = 0.0;
        double h = calculateH(startR, startC, exitR, exitC, mode);
        PathNode* startNode = new PathNode(to_string(startID), gCosts[startID], h);
        openList.push_back(startNode);

        while (!openList.empty()) {
            int curListID = findLowestFIndex(openList);
            PathNode* curNode = openList[curListID];
            int curID = stoi(curNode->name);
            int curR = curID / n;
            int curC = curID % n;
            delete curNode;
            openList.erase(openList.begin() + curListID);

            if (curR == exitR && curC == exitC) {break;}

            if (!visited[curID]) {visited[curID] = true;} else {continue;}
            for (int i = 0; i < 100; i++) {
                if (weightMatrix[curID][i] > 0 && !visited[i]) {
                    double newG = weightMatrix[curID][i] + gCosts[curID];
                    if (newG < gCosts[i]) {
                        gCosts[i] = newG;
                        parent[i] = curID;
                        int iR = i / n; int iC = i % n;
                        h = calculateH(iR, iC, exitR, exitC, mode);
                        PathNode* node = new PathNode(to_string(i), gCosts[i], h);
                        openList.push_back(node);
                    }
                }
            }
        }

        int backtrackID = convertCordToId(exitR, exitC, n);
        PathNode* head = nullptr;
        while (parent[backtrackID] != -1) {
            int backR = backtrackID / n;
            int backC = backtrackID % n;
            h = calculateH(backR, backC, exitR, exitC, mode);
            PathNode* node = new PathNode(convertCoordToStr(backR, backC), gCosts[backtrackID], h);
            head = addNodeToStart(head, node);
            backtrackID = parent[backtrackID];
        }
        int backR = backtrackID / n;
        int backC = backtrackID % n;
        h = calculateH(backR, backC, exitR, exitC, mode);
        PathNode* node = new PathNode(convertCoordToStr(backR, backC), gCosts[backtrackID], h);
        head = addNodeToStart(head, node);

        for (int i = 0; i < openList.size(); i++) {
            delete openList[i];
        }
        openList.clear();

        return head;
    }
