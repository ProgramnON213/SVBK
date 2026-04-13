#include <iostream>
#include <vector>
#include <string>
using namespace std;

int diagonalDiff(int arr[][1000], int row, int col, int x, int y) {
    int constMainDiag = x - y;
    int constAntiDiag = x + y;
    int sumMainDiag = 0;
    int sumAntiDiag = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i-j == constMainDiag) {
                sumMainDiag += arr[i][j];
            }
            if (i+j == constAntiDiag) {
                sumAntiDiag += arr[i][j];
            }
        }
    }

    return abs(sumAntiDiag - sumMainDiag);
}

int main() {
    int arr[][1000] = {{55,85,47,58},{31,4,60,67},{94,69,71,73},{51,62,64,90}};
    cout << diagonalDiff(arr,4,4,1,2);

    int arr1[][1000] = {{88,72,65,37},{82,84,34,12},{74,46,88,44}};
    cout << diagonalDiff(arr1,3,4,1,0);
}