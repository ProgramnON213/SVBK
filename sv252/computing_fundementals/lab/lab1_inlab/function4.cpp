#include <iostream>
using namespace std;

bool checkElementsUniqueness(int* arr, int n) {
    // Write your code 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {return false;}
        }
    }
    return true;
}

bool checkElementsUniqueness1(int* arr, int n) {
    int max = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {max = arr[i];}
    }
    int table[max+1];
    for (int i = 0; i < max+1; i++) {
        table[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (table[arr[i]] == 0) {table[arr[i]]++;}
        else {return false;}
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << checkElementsUniqueness(arr, n);
    delete[] arr;
}