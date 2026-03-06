/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2026
* Date: 27.01.2026
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "water_seven.h"

using namespace std;

bool testTask0(string filename, char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER], int shipHP, int repairCost) {
    bool result = readInput(filename, character, hp, skill, shipHP, repairCost);

    for (int i = 0; i < FIXED_CHARACTER; i++) {
        cout << character[i] << "/" << hp[i] << "/" << skill[i] << endl;
    }
    cout << "SHIP:" << shipHP << "/" << repairCost << endl;
    return result;
}

void testTask1() {
    cout << damageEvaluation(123, 100) << endl; // 150
    cout << damageEvaluation(455, 100) << endl; // 100
    cout << damageEvaluation(411, 253) << endl; // 380
    cout << damageEvaluation(1998, 100) << endl; // 100
    cout << damageEvaluation(0, 100) << endl; // 100
}

int testTask2(string filename, char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER], int shipHP, int repairCost) {
    readInput(filename, character, hp, skill, shipHP, repairCost);
    return conflictSimulation(character, hp, skill, shipHP, repairCost);
}

// cout << testTask2("task2a", character, hp, skill, shipHP, repairCost) << endl; // 334
// cout << testTask2("task2b", character, hp, skill, shipHP, repairCost) << endl; // 279

int main(int argc, const char * argv[]) {
    char character[FIXED_CHARACTER][MAX_NAME];
    int hp[FIXED_CHARACTER];
    int skill[FIXED_CHARACTER];
    int shipHP, repairCost;

    
    return 0;
}
