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
        int sum_to_reach = u - skill[luffy_idx];
        char other_character[FIXED_CHARACTER-2][MAX_NAME];
        int other_cost[FIXED_CHARACTER-2];
        int other_skill[FIXED_CHARACTER-2];
        set_other_character_stat(character, skill, hp, other_character, other_skill, other_cost, luffy_idx, usopp_idx);
        pick_character(other_character, other_cost, other_skill, duel, sum_to_reach);
    }

// Task 4
void decodeCP9Message(char character[FIXED_CHARACTER][MAX_NAME], 
    int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER], int conflictIndex, 
    int repairCost, char cipherText[], char resultText[]){
        //TODO: Output assign to resultText parameter
        int idx = 0, sum = 0;
        while (cipherText[idx+3] != '\0') {
            sum += cipherText[idx];
            idx++;
        }

        int xy = (cipherText[idx+1]-48)*10 + cipherText[idx+2]-48;
        if (sum%100 != xy) {
            resultText = {};
            return;
        }

        int key = (conflictIndex+repairCost) % 26;
        int block_length = (key%5) + 4;
        int block = 1;
        int result_idx = 0;
        bool is_stopped = false;
        while (!is_stopped) {
            int start = block*block_length-1;
            int end = (block-1)*block_length-1;
            if (start >= idx) {
                is_stopped = true;
                start = idx - 1;
            }
            for (int i = start; i > end; i--) {
                resultText[result_idx] = caesarChar(cipherText[i], -key);
                result_idx++;
            }
            block++;
        }
        resultText[result_idx] = '\0';
        char tempText[result_idx+100];
        strcpy(tempText, resultText);
        string strText = resultText;
        if (uppercase_and_find(tempText, result_idx+100, KEYWORDS_1) || uppercase_and_find(tempText, result_idx+100, KEYWORDS_2)) {
            strText += "_TRUE";
        }
        else {strText += "_FALSE";}
        strcpy(resultText, strText.c_str());
    }

// Task 5
int analyzeDangerLimit(int grid[MAX_GRID][MAX_GRID], int rows, int cols){
    int maxRowSum = 0, maxCell = 0;
    for (int i = 0; i < rows; i++) {
        int rowSum = 0;
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] >= 0) rowSum += grid[i][j];
            if (grid[i][j] > maxCell)   maxCell = grid[i][j];
        }
        if (rowSum > maxRowSum) maxRowSum = rowSum;
    }
    return maxRowSum + maxCell;
}


bool evaluateRoute(int grid[MAX_GRID][MAX_GRID], int rows, int cols, int dangerLimit){
    if (rows == 1 && cols == 1) {
        return (!(grid[0][0] == -1 && grid[0][0] > dangerLimit));
    }
    if (grid[0][0] == -1 || grid[rows-1][cols-1] == -1) {return false;}

    for (int j = 1; j < cols; j++) {
        if (grid[0][j] == -1)   {grid[0][j] = dangerLimit+1;}
        else grid[0][j] += grid[0][j-1];
    }
    for (int i = 1; i < rows; i++) {
        if (grid[i][0] == -1)   {grid[i][0] = dangerLimit+1;}
        else grid[i][0] += grid[i-1][0];
    }
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (grid[i][j] == -1)   grid[i][j] = dangerLimit+1;
            else grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
        }
    }
    return grid[rows-1][cols-1] <= dangerLimit;
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

bool uppercase_and_find(char input[], int input_length, const char target[]) {
    for (int i = 0; i < input_length; i++) {
        if (input[i] >= 97 && input[i] <= 122) {
            input[i] -= 32;
        }
    }
    char* pos = strstr(input, target);
    return (pos);
}

void pick_character(char other_character[FIXED_CHARACTER-2][MAX_NAME], 
    int other_cost[FIXED_CHARACTER-2], int other_skill[FIXED_CHARACTER-2], 
    char duel[FIXED_CHARACTER][MAX_NAME], int sum_to_reach) {
        if (sum_to_reach <= 0 || sum(other_skill, FIXED_CHARACTER-2) <= sum_to_reach) {
            duel = {};
            return;
        }
        int indexes[5] = {1, 1, 1, 1, 1};
        int min_cost = calculate_cost(indexes, other_cost, 5);  // Set max cost at min_cost in the beginning
        int temp_cost;
        int dream_team_indexes[5];
        copy(begin(indexes), end(indexes), begin(dream_team_indexes));
        
        for (int i = 0; i < 31; i++) {
            turn_i_into_binary(i, indexes, 5);
            temp_cost = calculate_cost(indexes, other_cost, 5);
            if (calculate_skill(indexes, other_skill, 5) >= sum_to_reach && temp_cost <= min_cost) {
                copy(begin(indexes), end(indexes), begin(dream_team_indexes));
                min_cost = temp_cost;
            }
        }

        put_indexes_to_duel(dream_team_indexes, duel, other_character, 5);
        return;
    }

int sum(int array[], int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += array[i];
    }
    return sum;
}

void turn_i_into_binary(int i, int indexes[], int len) {
    int temp = i;
    for (int j = 0; j < len; j++) {
        indexes[j] = temp%2;
        temp /= 2;
    }
    return;
}
int calculate_cost(int indexes[], int other_cost[],int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (indexes[i] == 1) {sum += other_cost[i];}
    }
    return sum;
}

int calculate_skill(int indexes[], int other_skill[], int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (indexes[i] == 1) {sum += other_skill[i];}
    }
    return sum;
}

void put_indexes_to_duel(int dream_team_indexes[], char duel[FIXED_CHARACTER][MAX_NAME], 
    char other_character[FIXED_CHARACTER-2][MAX_NAME], int len) {
    int duel_index = 0;
    for (int i = 0; i < len; i++) {
        if (dream_team_indexes[i] == 1) {
            strcpy(duel[duel_index], other_character[i]);
            duel_index++;
        }
    }
    return;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
