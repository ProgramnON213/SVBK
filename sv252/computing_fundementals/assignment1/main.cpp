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

// Cấu trúc Testcase sử dụng mảng tĩnh
struct TestCase5a {
    int id;
    const char* description;
    int grid[MAX_GRID][MAX_GRID];
    int rows;
    int cols;
    int expectedOutput;
};
void testTask5a() {
    // Khởi tạo mảng testcases. 
    // Các ô không được khai báo rõ ràng sẽ tự động được gán giá trị 0 (padding),
    // nhưng hàm analyzeDangerLimit chỉ đọc đến giới hạn 'rows' và 'cols' nên không bị ảnh hưởng.
    TestCase5a testCases[] = {
        {1, "Ma tran hon hop co ban", 
            {{0, 1, -1, 2}, 
             {-1, 3, 1, 0}, 
             {-1, -1, -1, 1}}, 
         3, 4, 7},
             
        {2, "maxCell khong nam trong hang co maxRowSum", 
            {{3, -1, -1}, 
             {1, 1, 2}, 
             {0, 0, 0}}, 
         3, 3, 7},
             
        {3, "Khu vuc hoan toan an toan (Toan 0)", 
            {{0, 0, 0}, 
             {0, 0, 0}}, 
         2, 3, 0},
             
        {4, "Khu vuc cuc ky nguy hiem (Toan 3)", 
            {{3, 3, 3}, 
             {3, 3, 3}, 
             {3, 3, 3}}, 
         3, 3, 12},
             
        {6, "Ma tran 1x1 (Nho nhat)", 
            {{2}}, 
         1, 1, 4},
            
        {7, "Ma tran chi co 1 hang", 
            {{-1, 1, 2, 3, -1}}, 
         1, 5, 9},
            
        {8, "Ma tran chi co 1 cot", 
            {{-1}, 
             {2}, 
             {3}, 
             {-1}}, 
         4, 1, 6}
    };

    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    int passed = 0;

    for (int i = 0; i < numTests; ++i) {
        int result = analyzeDangerLimit(testCases[i].grid, testCases[i].rows, testCases[i].cols);
        
        cout << "Testcase " << testCases[i].id << ": " << testCases[i].description << "\n";
        if (result == testCases[i].expectedOutput) {
            cout << "  -> [PASS] Expected: " << testCases[i].expectedOutput << " | Got: " << result << "\n";
            passed++;
        } else {
            cout << "  -> [FAIL] Expected: " << testCases[i].expectedOutput << " | Got: " << result << "\n";
        }
        cout << "----------------------------------------\n";
    }
    
    cout << "\nTong ket: Passed " << passed << "/" << numTests << " testcases.\n";
}

// Cấu trúc Testcase
struct TestCase5b {
    int id;
    const char* description;
    int grid[MAX_GRID][MAX_GRID];
    int rows;
    int cols;
    int dangerLimit;
    bool expectedOutput;
};

void testTask5b() {
    TestCase5b testCases[] = {
        {1, "Co lo trinh va an toan", 
            {{0, 1, 0}, 
             {0, 2, 0}, 
             {0, 0, 0}}, 3, 3, 5, true},
             
        {2, "Nhieu lo trinh, phai chon duong toi uu (dp)", 
            {{0, 5, 0}, 
             {1, 1, 1}, 
             {5, 5, 0}}, 3, 3, 4, true},
             
        {3, "Co duong nhung vuot nguong nguy hiem", 
            {{1, 2, 3}, 
             {1, -1, 2}, 
             {1, 1, 1}}, 3, 3, 3, false},
             
        {4, "Bi chan boi hang rao -1", 
            {{0, 1, 0}, 
             {-1, -1, -1}, 
             {0, 0, 0}}, 3, 3, 10, false},
             
        {5, "Diem xuat phat bi chan", 
            {{-1, 0}, 
             {0, 0}}, 2, 2, 100, false},
             
        {6, "Ma tran 1 chieu (vuot limit)", 
            {{0, 1, 2, 3}}, 1, 4, 5, false}
    };

    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    int passed = 0;

    for (int i = 0; i < numTests; ++i) {
        bool result = evaluateRoute(testCases[i].grid, testCases[i].rows, testCases[i].cols, testCases[i].dangerLimit);
        
        cout << "Testcase " << testCases[i].id << ": " << testCases[i].description << "\n";
        if (result == testCases[i].expectedOutput) {
            cout << "  -> [PASS] Expected: " << (testCases[i].expectedOutput ? "true" : "false") 
                 << " | Got: " << (result ? "true" : "false") << "\n";
            passed++;
        } else {
            cout << "  -> [FAIL] Expected: " << (testCases[i].expectedOutput ? "true" : "false") 
                 << " | Got: " << (result ? "true" : "false") << "\n";
        }
        cout << "----------------------------------------\n";
    }
    
    cout << "\nTong ket: Passed " << passed << "/" << numTests << " testcases.\n";
}

// cout << testTask2("task2a", character, hp, skill, shipHP, repairCost) << endl; // 334
// cout << testTask2("task2b", character, hp, skill, shipHP, repairCost) << endl; // 279

int main(int argc, const char * argv[]) {
    testTask5b();
    return 0;
}
