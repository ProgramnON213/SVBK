#ifndef PATHNODE_H
#define PATHNODE_H

#include <string>
using namespace std;

struct PathNode {
    string name;
    double f;
    double g;
    double h;
    PathNode* next;

    PathNode();
    PathNode(string name, double g, double h);
    ~PathNode();
};

PathNode* addNodeToStart(PathNode* head, PathNode* node);

#endif