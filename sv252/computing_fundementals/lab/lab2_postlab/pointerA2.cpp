#include <iostream>
using namespace std;

void reverse(int *ptr, int n) {
    for (int i = 0; i < n/2; i++) {
        int temp = *(ptr + i);
        *(ptr + i) = *(ptr + n - i - 1);
        *(ptr + n - i - 1) = temp;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    reverse(arr, sizeof(arr) / sizeof(arr[0]));
    cout << arr[0];
    for (int i = 1; i < sizeof(arr) / sizeof(arr[0]); i++) {
        cout << ", " << arr[i];
    }
}