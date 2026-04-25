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