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
    if (shipHP < 455 && is_sum_of_digit_perfect(shipHP)) {
        repairCost = ceil(repairCost*1.5);
    }
    return repairCost;
}

// Task 2
int conflictSimulation(
    char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
    int shipHP, int repairCost){
        int luffy_idx = find_names(character, "LUFFY");
        int usopp_idx = find_names(character, "USOPP");
        int conflictIndex = round(skill[luffy_idx] - skill[usopp_idx] + repairCost/100.0 + (500-shipHP)/50.0);
        return repeatingConflictSimulation(conflictIndex);
    }

// Task 3
void resolveDuel(
    char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
    int conflictIndex, int repairCost, char duel[FIXED_CHARACTER][MAX_NAME]){
        //TODO: Output assign to duel parameter
        int luffy_idx = find_names(character, "LUFFY");
        int usopp_idx = find_names(character, "USOPP");
        int u = ceil(skill[usopp_idx] + conflictIndex/20.0 + repairCost/500.0);
        if (skill[luffy_idx] >= u) {return;}
        int sum_to_reach = u - skill[luffy_idx];
        char other_character[FIXED_CHARACTER-2][MAX_NAME];
        int other_cost[FIXED_CHARACTER-2];
        int other_skill[FIXED_CHARACTER-2];
        set_other_character_stat(character, skill, hp, other_character, other_skill, other_cost, luffy_idx, usopp_idx);
        for (int i = 0; i < FIXED_CHARACTER-2; i++) {
            cout << other_character[i] << "/" << other_skill[i] << "/" << other_cost[i] << endl;
        }
        // TODO: Find the idxes needed, put it in an array
        // The idxes should be refer to the other_character arrays 
        // using other_character and add the sorted array to duel
    }

// Task 4
void decodeCP9Message(char character[FIXED_CHARACTER][MAX_NAME], 
    int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER], int conflictIndex, 
    int repairCost, char cipherText[], char resultText[]){
        //TODO: Output assign to resultText parameter
        int idx = 0, sum = 0;
        while (cipherText[idx] != '#') {
            sum += cipherText[idx];
            idx++;
        }
        int xy = (cipherText[idx+1]-48)*10 + cipherText[idx+2]-48;
        if (sum%100 == xy) {resultText = {};}
        else {
            int key = (conflictIndex+repairCost) % 26;
            int block_length = (key%5) + 4;
            int number_of_blocks = ceil((float)idx/block_length);
            char blocks[number_of_blocks][block_length];
            
            idx = 0;
            while (cipherText[idx] != '#') {
                blocks[idx/block_length][block_length - idx%block_length - 1] = caesarChar(cipherText[idx], -key);
                idx++;
            }
            int temp = 0;
            for (int i = 0; i < number_of_blocks-1; i++) {
                for (int j = 0; j < block_length; j++) {
                    resultText[i*block_length+j] = blocks[i][j];
                    temp += 1;
                }
            }
            for (int i = idx%number_of_blocks; i < block_length; i++) {
                resultText[temp] = blocks[number_of_blocks][i];
                temp++;
            }
            for (int i = 0; i < temp; i++) {
                cout << resultText[i] << "/";
            }
        }
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

// Check if the sum of digit is the first 2 perfect numbers
bool is_sum_of_digit_perfect(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n%10;
        n /= 10;
    }
    return (sum == 6 || sum == 28);
}

// Repeated conflict simulation
int repeatingConflictSimulation(int conflictIndex) {
    int count = 0;
    while (conflictIndex < 255 && count < 10) {
        int id = conflictIndex % 6;
        switch (id)
        {
        case 0:
            conflictIndex += 255;
            break;
        case 1:
            conflictIndex += 20;
            break;
        case 2:
            conflictIndex += 50;
            break;
        case 3:
            conflictIndex += 70;
            break;
        case 4:
            conflictIndex += 90;
            break;
        case 5:
            conflictIndex += 100;
            break;
        }
        count += 1;
    }
    return conflictIndex;
}

void set_other_character_stat(char character[FIXED_CHARACTER][MAX_NAME], 
    int skill[FIXED_CHARACTER], int hp[FIXED_CHARACTER],
    char other_character[FIXED_CHARACTER-2][MAX_NAME], int other_skill[FIXED_CHARACTER-2], 
    int other_cost[FIXED_CHARACTER-2], int luffy_idx,  int usopp_idx) {
        int idx = 0;
        for (int i = 0; i < FIXED_CHARACTER; i++) {
            if (i != luffy_idx && i != usopp_idx) {
                strcpy(other_character[idx], character[i]);
                other_skill[idx] = skill[i];
                other_cost[idx] = hp[i] % 10 + 1;
                idx++;
            }
        }
    return;
}

char caesarChar(char c, int key) {
    if (47 < c && c < 58) {
         c += key;
         if (c < 48)    c += 10;
         else if (c > 57)   c -= 10;
    }
    else if (64 < c && c < 91) {
        c += key;
        if (c < 65)     c += 26;
        else if (c > 90)    c -= 26;
    }
    else if (96 < c && c < 123) {
        c += key;
        if (c < 97)     c += 26;
        else if (c > 122)   c -= 26;
    }
    return c;
}


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
