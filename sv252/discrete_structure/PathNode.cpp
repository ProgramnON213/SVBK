#include "PathNode.h"

PathNode::PathNode() {
    this->name = "default";
    this->g = 0;
    this->h = 0;
    this->f = g + h;
    this->next = nullptr;
}

PathNode::PathNode(string name, double g, double h) {
    this->name = name;
    this->g = g;
    this->h = h;
    this->f = g + h;
    this->next = nullptr;
}

PathNode::~PathNode() {
    delete this->next;
}

PathNode* addNodeToStart(PathNode* head, PathNode* node) {
    if (head != nullptr) {
        node->next = head;
    }
    return node;
}