#include <iostream>
using namespace std;

void insertRow(int**& matrix, int r, int c, int* rowArr, int row) {
    // TODO
    if (r<0 || c<0 || row > r || row < 0) {return;}
    int** newMatrix = new int*[r+1];
    for (int i = 0; i < row; i++) {
        newMatrix[i] = matrix[i];
    }
    newMatrix[row] = rowArr;
    for (int i = row+1; i < r+1; i++) {
        newMatrix[i] = matrix[i-1];
    }
    delete[] matrix;
    matrix = newMatrix;
}

int main() {
    int** m = new int*[2];
    m[0] = new int[2]; m[0][0] = 1; m[0][1] = 2;
    m[1] = new int[2]; m[1][0] = 1; m[1][1] = 3;
    int *n = new int[2];
    n[0] = 5; n[1] = 6;
    insertRow(m, 2, 2, n, 2);
    cout << m[0][0] << ' ' << m[0][1] << '\n' << m[2][0] << ' ' << m[2][1];
}