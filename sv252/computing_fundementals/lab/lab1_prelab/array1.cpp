#include <iostream>
#include <climits>
using namespace std;

int sumOfOneColumn(int arr[][1000], int row, int col) {
    int sum = 0;
    for (int i = 0; i < row; i++) {
        sum += arr[i][col];
    }
    return sum;
}

int findMaxColumn(int arr[][1000], int row, int col) {
    int maxSum = sumOfOneColumn(arr, row, 0);
    int maxIdx = 0;
    for (int i = 1; i < col; i++) {
        if (sumOfOneColumn(arr, row, i) >= maxSum) {
            maxIdx = i;
            maxSum = sumOfOneColumn(arr, row, i);
        }
    }
    return maxIdx;
}

int main () {
    int arr[][1000] = {{-44,64,-6},{87,92,-19},{-92,53,-38},{-39,-92,21}};
    cout << findMaxColumn(arr, 4, 3);

    int arr1[][1000] = {{-92,78,-2,-58,-37},{44,-4,30,-69,22}};
    cout << findMaxColumn(arr1, 2,5);
}
