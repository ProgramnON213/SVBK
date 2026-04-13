#include <iostream>
#include <string>
using namespace std;

bool isSymmetric(int arr[][1000], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = i; j < col; j++) {
            if (arr[i][j] != arr[j][i]) {return false;}
        }
    }
    return true;
}

int main() {
    int arr[][1000] = {{1,4,6}, {4,5,3}, {6,3,9}};
    cout << isSymmetric(arr,3,3);

    int arr1[][1000] = {{1,9,6}, {4,5,3}, {6,3,9}};
    cout << isSymmetric(arr1,3,3);
}