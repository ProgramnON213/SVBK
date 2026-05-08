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

SCP* cloneSCP(SCP* original) {
    // Student answer
    SCP* res = new SCP;
    res->id = original->id;
    res->objClass = original->objClass;
    res->speConProcedures = original->speConProcedures;
    res->description = original->description;
    res->numAddendums = original->numAddendums;
    res->addendums = new string[original->numAddendums];
    for (int i = 0; i < res->numAddendums; i++) {
        res->addendums[i] = original->addendums[i];
    }
    return res;
}

int main() {
    string* addendums = new string[2];
    addendums[0] = "Document #055-1: An Analysis of SCP-055\nThe author puts forward the hypothesis that SCP-055 was never formally acquired.";
    addendums[1] = "Document #055-2: Report of Dr. John Marachek\nSurvey team #19-055-127BXE was successfully able to enter SCP-055's container and ascertain the appearance.";

    SCP* obj = new SCP {55, 2, "Object is kept within a five (5) by five (5) by two point five (2.5) meter square room.", "All known information about the object is that it is not round.", addendums, 2};

    SCP* newObj = cloneSCP(obj);

    obj->id = 1;
    cout << obj->id << " " << newObj->id << "\n";

    delete [] obj->addendums;
    delete obj;

    delete [] newObj->addendums;
    delete newObj;
}