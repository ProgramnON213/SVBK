#include <iostream>
#include <string>
using namespace std;

bool isPrime(int n) {
    if (n%2 == 0 || n < 0) {return false;}
    int maxNumToCheck = n/2+1;
    for (int i = 3; i <= maxNumToCheck; i+=2) {
        if (n % i == 0) {return false;}
    }
    return true;
}

int primeColumns(int arr[][1000], int row, int col) {
    int count = 0;
    for (int i = 0; i < col; i++) {
        int colTotal = 0;
        for (int j = 0; j < row; j++) {
            colTotal += arr[j][i];
        }
        if (isPrime(colTotal)) {count++;}
    }
    return count;
}

int main() {
    int arr1[][1000] = {{-64,-28,-3,64},{-56,90,57,-31}};
    cout << primeColumns(arr1,2,4) << endl;
    
    int arr2[][1000] = {{34,-15,11,-70,-23,24},{-39,-90,63,-45,-52,48},{-42,92,55,92,82,81}};
    cout << primeColumns(arr2,3,6) << endl;
}