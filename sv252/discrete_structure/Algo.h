#ifndef ALGO_H
#define ALGO_H

#include "PathNode.h"
#include <vector>

PathNode* findSocialPath(double adjMatrix[100][100], int startPerson, int goalPerson);
PathNode* findDronePath(double weightMatrix[100][100], int coords[100][2], int startPoint, 
    int goalPoint, int mode);
PathNode* findWarehousePath(int warehouse[100][100], int m, int n, int startX,
    int startY, int goalX, int goalY, int mode);
PathNode* findEvacuationPath(int floorPlan[100][100], int m, int n, 
                             int startX, int startY, int exitX, int exitY, 
                             double weightMatrix[100][100], int mode);

int findLowestFIndex(vector<PathNode*> list);
double* setupHCost1(double adjMatrix[100][100]);

string convertCoordToStr(int coord[2]);
double calculateH(int x1, int y1, int x2, int y2, int mode);

int convertCordToId(int r, int c, int numCol);
string getName(int childR, int childC, int parR, int parC);
string convertCoordToStr(int a, int b);


#endif