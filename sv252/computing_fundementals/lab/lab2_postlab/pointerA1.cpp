#include <iostream>
using namespace std;

int findMax(int* ptr, int n) {
    int max = *ptr;
    for (int i = 0; i < n; i++) {
        if (*(ptr + i) > max) {
            max = *(ptr + i);
        }
    }
    return max;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    cout << findMax(arr, sizeof(arr) / sizeof(arr[0]));
}