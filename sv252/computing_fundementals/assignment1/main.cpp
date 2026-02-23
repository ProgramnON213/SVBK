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



int main(int argc, const char * argv[]) {
    char character[FIXED_CHARACTER][MAX_NAME];
    int hp[FIXED_CHARACTER];
    int skill[FIXED_CHARACTER];
    int shipHP;
    int repairCost;
    readInput("opw_tc_01_input", character, hp, skill, shipHP, repairCost);
    cout << shipHP << " " << repairCost << endl;
    for (int i = 0; i < FIXED_CHARACTER; i++) {
        cout << character[i] << "/" << hp[i] << "/" << skill[i] << endl;
    }
    return 0;
}
