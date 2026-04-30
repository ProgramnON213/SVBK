#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n%2 == 0 || n < 0) {return false;}
    int maxNumToCheck = n/2+1;
    for (int i = 3; i <= maxNumToCheck; i+=2) {
        if (n % i == 0) {return false;}
    }
    return true;
}

int takeSumRow(int n[], int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += n[i];
    }
    return sum;
}

int takeSumCol(int n[][1000], int row, int col) {
    int sum = 0;
    for (int i = 0; i < row; i++) {
        sum += n[i][col];
    }
    return sum;
}

int specialCells(int arr[][1000], int row, int col) {
    bool isTotalRowPrime[row];
    bool isTotalColPrime[col];
    for (int i = 0; i < row; i++) {
        isTotalRowPrime[i] = isPrime(takeSumRow(arr[i], col));
    }
    for (int i = 0; i < col; i++) {
        isTotalColPrime[i] = isPrime(takeSumCol(arr, row, i));
    }
    int count = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (isTotalRowPrime[i] && isTotalColPrime[j]) {count++;}
        }
    }
    return count;
}

int main() {
    int arr[][1000] = {{37,53,74},{12,37,60},{98,13,15}};
    cout << specialCells(arr,3,3);
}