#include <iostream>
#include <string>
using namespace std;

struct SCP {
    // Student answer
    int id;
    int objClass;
    string speConProcedures;
    string description;
    string* addendums;
    int numAddendums;
};

void addAddendum(SCP &obj, string addendum) {
    // Student answer
    obj.numAddendums++;
    string* temp = new string[obj.numAddendums];
    for (int i = 0; i < obj.numAddendums-1; i++) {
        temp[i] = obj.addendums[i];
    }
    obj.addendums = temp;
    obj.addendums[obj.numAddendums-1] = addendum;
}

int main() {
string* addendums = new string [1];
addendums[0] = "Request 500-1774-k\nDr. [500-0022F] has requested one (1) SCP-500 pill for testing with SCP-038. Request has been approved.";

SCP obj {500, 0, "SCP-500 must be stored in a cool and dry place away from bright light.", "SCP-500 is a small plastic can which at the time of writing contains forty-seven (47) red pills.", addendums, 1};

addAddendum(obj, "Request 500-1862-b\nDr. Gears has requested one (1) SCP-500 pill for testing in SCP-914. Request has been approved.");

cout << obj.addendums[0];

delete [] obj.addendums;
}