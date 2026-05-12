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

SCP** sortDatabase(SCP** arr, int n) {
    // Student answer
    for (int i = 0; i < n; i++) {
        SCP* curMin = arr[i];
        for (int j = i; j < n; j++) {
            if (curMin->id > arr[j]->id) {
                curMin = arr[j];
            }
        }
        SCP temp = *curMin;
        *curMin = *arr[i];
        *arr[i] = temp;
    }
    return arr;
}