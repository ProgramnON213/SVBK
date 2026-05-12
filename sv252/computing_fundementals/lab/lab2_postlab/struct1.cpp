#include <iostream>
using namespace std;

struct SCP {
    int id;
    int objClass;
    string speConProcedures;
    string description;
    string* addendums;
    int numAddendums;
};

int compareObjectClass(const SCP &objA, const SCP &objB) {
    if (objA.objClass > objB.objClass) {return 1;}
    if (objA.objClass < objB.objClass) {return -1;}
    return 0;
}