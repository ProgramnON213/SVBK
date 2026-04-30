#include <iostream>
using namespace std;

int getSumOf2x2Matrix(int arr[][1000], int row, int col) {
    return arr[row][col] + arr[row+1][col] + arr[row][col+1] + arr[row+1][col+1];
}

int subMatrix(int arr[][1000], int row, int col) {
    int count = 0;
    for (int i = 0; i < row-1; i++) {
        for (int j = 0; j < col-1; j++) {
            if (getSumOf2x2Matrix(arr, i, j) % 2 == 1) {count++;}
        }
    }
    return count;
}

int main() {
int arr[][1000] ={{44,45,89},{82,91,34},{83,87,33},{65,51,66}};
cout << subMatrix(arr,4, 3);
}