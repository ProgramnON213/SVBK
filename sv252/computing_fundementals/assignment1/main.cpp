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

void testTask3(char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER], 
    int repairCost, char duel[FIXED_CHARACTER][MAX_NAME], int shipHP) {
        string filename = "testcases/task3f";
        readInput(filename, character, hp, skill, shipHP, repairCost);
        resolveDuel(character, hp, skill, 0, repairCost, duel);
        for (int i = 0; i < FIXED_CHARACTER; i++) {
            cout << duel[i] << endl;
        }
    }

void testTask4() {
    char dummyNames[7][MAX_NAME] = {"A", "B", "C", "D", "E", "F", "G"};
    int dummyHP[7] = {100, 100, 100, 100, 100, 100, 100};
    int dummySkill[7] = {10, 10, 10, 10, 10, 10, 10};
    char cipherText[1000];
    char resultText[1000];

    strcpy(cipherText, "hgfedC76543 #74");
    decodeCP9Message(dummyNames, dummyHP, dummySkill, 10, 18, cipherText, resultText);
    cout << resultText << endl; //Abcdef 12345_FALSE

    strcpy(cipherText, "5Ff4Ee#47");
    decodeCP9Message(dummyNames, dummyHP, dummySkill, 0, 5, cipherText, resultText);
    cout << resultText << endl; //9aA0zZ_FALSE

    strcpy(cipherText, "tseT#16");
    decodeCP9Message(dummyNames, dummyHP, dummySkill, 26, 0, cipherText, resultText);
    cout << resultText << endl; //Test_FALSE

    strcpy(cipherText, "WbazYX#81");
    decodeCP9Message(dummyNames, dummyHP, dummySkill, 20, 5, cipherText, resultText);
    cout << resultText << endl; //abcXYZ_FALSE

    strcpy(cipherText, "lleHPC o9#36");
    decodeCP9Message(dummyNames, dummyHP, dummySkill, 26, 0, cipherText, resultText);
    cout << resultText << endl; //Hello CP9_TRUE

    strcpy(cipherText, "TFJOFZCCPM#58");
    decodeCP9Message(dummyNames, dummyHP, dummySkill, 1, 0, cipherText, resultText);
    cout << resultText << endl; //ENIESLOBBY_TRUE

    strcpy(cipherText, "llehpc o9#32");
    decodeCP9Message(dummyNames, dummyHP, dummySkill, 26, 0, cipherText, resultText);
    cout << resultText << endl; //hello cp9_FALSE

    strcpy(cipherText, "llehpc o9##67");
    decodeCP9Message(dummyNames, dummyHP, dummySkill, 26, 0, cipherText, resultText);
    cout << resultText << endl; //hello cp#9_FALSE

    strcpy(cipherText, "lleHPC o9#99");
    decodeCP9Message(dummyNames, dummyHP, dummySkill, 26, 0, cipherText, resultText);
    cout << resultText << endl; //(empty)
}

// cout << testTask2("task2a", character, hp, skill, shipHP, repairCost) << endl; // 334
// cout << testTask2("task2b", character, hp, skill, shipHP, repairCost) << endl; // 279

int main(int argc, const char * argv[]) {
    char character[FIXED_CHARACTER][MAX_NAME];
    int hp[FIXED_CHARACTER];
    int skill[FIXED_CHARACTER];
    int shipHP, repairCost;
    char duel[FIXED_CHARACTER][MAX_NAME];
    testTask4();
    return 0;
}
