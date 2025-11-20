#include <iostream>
using namespace std;

bool sudoku(char board[9][9]);

int main() {
char board[9][9] = {
    {'5','3','.','.','7','.','.','.','.'},
    {'6','.','.','1','9','5','.','.','.'},
    {'.','9','8','.','.','.','.','6','.'},
    {'8','.','.','.','6','.','.','.','3'},
    {'4','.','.','8','.','3','.','.','1'},
    {'7','.','.','.','2','.','.','.','6'},
    {'.','6','.','.','.','.','2','8','.'},
    {'.','.','.','4','1','9','.','.','5'},
    {'.','.','.','.','8','.','.','7','9'}
};
    cout << sudoku(board);
    return 0;
}

bool isRepeated(char str[9]);
bool sudoku(char board[9][9]) {
    // First, test rows
    for (int i = 0; i < 9; i++) {
        char temp[9];
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.') temp[j] = board[i][j];
            else temp[j] = '0';
        }
        if (isRepeated(temp))   return false;
    }
    // Next, test columns
    for (int i = 0; i < 9; i++) {
        char temp[9];
        for (int j = 0; j < 9; j++) {
            if (board[j][i] != '.') temp[j] = board [j][i];
            else temp[j] = '0';
        }
        if (isRepeated(temp))   return false;
    }
    // Last, test boxes
    for (int boxCol = 0; boxCol < 9; boxCol += 3) {
        for (int boxRow = 0; boxRow < 9; boxRow += 3) {

            char temp[9];
            int count = 0;
            for (int i = boxCol; i < boxCol + 3; i++) {
                for (int j = boxRow; j < boxRow + 3; j++) {
                    if (board[i][j] != '.') temp[count] = board[i][j];
                    else temp[count] = '0';
                    count += 1;
                }
            }
            if (isRepeated(temp))   return false;
        }
    }
    return true;
}

bool isRepeated(char str[9]) {
    bool seen[10] = {false, false, false, false, false, false, false, false, false, false};
    for (int i = 0; i < 9; i++) {
        if (str[i] == '0')  continue;
        else {
            if (seen[str[i]-48] == true)    return true;
            else    seen[str[i]-48] = true;
        }
    }
    return false;
}