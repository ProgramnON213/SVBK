#include <iostream>
#include <string>
using namespace std;

int ascendingRows(int arr[][1000], int row, int col) {
    int count = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 1; j < col; j++) {
            if (arr[i][j] < arr[i][j-1]) {break;}
            if (j == col-1) {count++;}
        }
    }
    return count;
}

int main() {
    int arr1[][1000] = {{32,4,9},{-80,37,71},{-91,-79,-55}};
    cout << ascendingRows(arr1,3, 3);
    int arr2[][1000] = {{-28,-8,-60,18},{-100,44,-1,24},{-94,92,-70,75}};
    cout << ascendingRows(arr2,3,4);
}