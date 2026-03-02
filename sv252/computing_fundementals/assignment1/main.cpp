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
    cout << "=== Task 4: Decode CP9 Message ===" << endl;
    char character[FIXED_CHARACTER][MAX_NAME];
    int hp[FIXED_CHARACTER];
    int skill[FIXED_CHARACTER];
    int shipHP, repairCost;

    string filename = "opw_tc_01_input";
    readInput(filename, character, hp, skill, shipHP, repairCost);

    int adjustedRepairCost = damageEvaluation(shipHP, repairCost);
    int conflictIndex = conflictSimulation(character, hp, skill, shipHP, adjustedRepairCost);

    // Test valid message with CP9
    char cipherText1[] = "D 0KXN#89";
    char resultText1[1000] = {};
    decodeCP9Message(character, hp, skill, conflictIndex, adjustedRepairCost, cipherText1, resultText1);
    cout << "Test 1 - Cipher: " << cipherText1 << " -> Decoded: " << resultText1 << endl;

    // Test invalid checksum
    char cipherText2[] = "HELLO#00";
    char resultText2[1000] = {};
    decodeCP9Message(character, hp, skill, conflictIndex, adjustedRepairCost, cipherText2, resultText2);
    cout << "Test 2 - Cipher: " << cipherText2 << " -> Decoded: \"" << resultText2 << "\" (expected empty)" << endl;
    cout << endl;
    return 0;
}
