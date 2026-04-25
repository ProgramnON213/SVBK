#include <iostream>
#include <cstring>
using namespace std;


const int MAX_WORD = 1000;
const int MAX_LENGTH = 30;  //Should be 31 because NULL

bool isSeen(char seen[MAX_WORD][MAX_LENGTH], char *pos, int seenIndex) {
    for (int i = 0; i < seenIndex; i++) {
        if (strcmp(seen[i], pos) == 0) {
            return true;
        }
    }
    return false;
}

void printFirstRepeatedWord(char str[]) {
    // TODO
    char seen[MAX_WORD][MAX_LENGTH];
    int seenIndex = 0;
    char *pos = strtok(str, " ");
    while (pos != NULL) {
        if (isSeen(seen, pos, seenIndex)) {
            cout << pos;
            return;
        }
        strcpy(seen[seenIndex], pos);
        seenIndex++;
        pos = strtok(NULL, " ");
    }
    cout << "No Repetition";
}

int main() {
    char str[] = "car taxi bike bike car taxi" ;
    printFirstRepeatedWord(str);
}