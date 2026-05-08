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

#include <iomanip>
#include <sstream>
string convertToString(SCP obj) {
    // Student answer
    stringstream ss;

    ss << "Item #: SCP-" << setfill('0') << setw(3) << obj.id << endl;

    string objClass;
    if (obj.objClass == 0) {objClass = "Safe";}
    if (obj.objClass == 1) {objClass = "Euclid";}
    if (obj.objClass == 2) {objClass = "Keter";}
    ss << "Object Class: " << objClass << endl;

    ss << "Special Containment Procedures: " << obj.speConProcedures << endl;

    ss << "Description: " << obj.description << endl;

    for (int i = 0; i < obj.numAddendums; i++) {
        ss << obj.addendums[i] << endl;
    }

    return ss.str();
}

int main() {
    string* addendums = new string[2];
    addendums[0] = "Document #055-1: An Analysis of SCP-055\nThe author puts forward the hypothesis that SCP-055 was never formally acquired.";
    addendums[1] = "Document #055-2: Report of Dr. John Marachek\nSurvey team #19-055-127BXE was successfully able to enter SCP-055's container and ascertain the appearance.";

    SCP obj {55, 2, "Object is kept within a five (5) by five (5) by two point five (2.5) meter square room.", "All known information about the object is that it is not round.", addendums, 2};

    cout << convertToString(obj);

    delete [] addendums;
}