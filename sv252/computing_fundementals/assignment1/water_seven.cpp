#include "water_seven.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
//Task 0
bool readInput(
    const string &filename,
    char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], 
    int skill[FIXED_CHARACTER], int &shipHP, int &repairCost){
        fstream f(filename);
        if (!f.is_open()) {return false;}
        string line, temp;
        int idx = 0;
        while (!f.eof()) {
            char name[MAX_NAME];
            int stat1, stat2;
            f >> name;
            f >> stat1 >> stat2;
            if (strcmp(name, "GOING_MERRY") == 0) {
                shipHP = stat1;
                repairCost = stat2;
            }
            else {
                int pos = find_names(character, name);
                if (pos == -1) {
                    pos = idx;
                    idx++;
                }
                strcpy(character[pos], name);
                hp[pos] = stat1;
                skill[pos] = stat2;
            }
        }
        return false;
}



// Task 1
int damageEvaluation(int shipHP, int repairCost){
    return 0;
}

// Task 2
int conflictSimulation(
    char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
    int shipHP, int repairCost){
        return 0;
    }

// Task 3
void resolveDuel(
    char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
    int conflictIndex, int repairCost, char duel[FIXED_CHARACTER][MAX_NAME]){
        //TODO: Output assign to duel parameter
    }

// Task 4
void decodeCP9Message(char character[FIXED_CHARACTER][MAX_NAME], 
    int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER], int conflictIndex, 
    int repairCost, char cipherText[], char resultText[]){
        //TODO: Output assign to resultText parameter
    }

// Task 5
int analyzeDangerLimit(int grid[MAX_GRID][MAX_GRID], int rows, int cols){
    return 0;
}


bool evaluateRoute(int grid[MAX_GRID][MAX_GRID], int rows, int cols, int dangerLimit){
    return false;
}


// Helper function

// Return index if found, -1 if not
int find_names(char characters[FIXED_CHARACTER][MAX_NAME], string target) {
    for (int i = 0; i < FIXED_CHARACTER; i++) {
        if (characters[i] == target) {return i;}
    }
    return -1;
}


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
