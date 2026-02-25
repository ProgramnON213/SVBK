/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2025
 * Date: 07.02.2025
 */

#ifndef _WATER_SEVEN_CAMPAIGN_H_
#define _WATER_SEVEN_CAMPAIGN_H_

#include "main.h"

const int MAX_NAME = 100;
const int FIXED_CHARACTER = 7;
const int MAX_GRID = 50;

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

//Task 0
bool readInput(
    const string &filename,
    char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], 
    int skill[FIXED_CHARACTER], int &shipHP, int &repairCost);

// Task 1
int damageEvaluation(int shipHP, int repairCost);

// Task 2
int conflictSimulation(
    char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
    int shipHP, int repairCost);

// Task 3
void resolveDuel(
    char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
    int conflictIndex, int repairCost, char duel[FIXED_CHARACTER][MAX_NAME]);

// Task 4
const char KEYWORDS_1[] = "CP9";
const char KEYWORDS_2[] = "ENIESLOBBY"; 
void decodeCP9Message(char character[FIXED_CHARACTER][MAX_NAME], 
    int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER], int conflictIndex, 
    int repairCost, char cipherText[], char resultText[]);

// Task 5
int analyzeDangerLimit(int grid[MAX_GRID][MAX_GRID], int rows, int cols);
bool evaluateRoute(int grid[MAX_GRID][MAX_GRID], int rows, int cols, int dangerLimit);

// Helper
int find_names(char characters[FIXED_CHARACTER][MAX_NAME], string target);
bool is_sum_of_digit_perfect(int n);
int repeatingConflictSimulation(int conflictIndex);
void set_other_character_stat(char character[FIXED_CHARACTER][MAX_NAME], 
    int skill[FIXED_CHARACTER], int hp[FIXED_CHARACTER],
    char other_character[FIXED_CHARACTER-2][MAX_NAME], int other_skill[FIXED_CHARACTER-2], 
    int other_cost[FIXED_CHARACTER-2], int luffy_idx,  int usopp_idx);
char caesarChar(char c, int key);
bool uppercase_and_find(char input[], int input_length, const char target[]);

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////

#endif // _WATER_SEVEN_CAMPAIGN_H_