#include <iostream>
#include <string>
using namespace std;

int minimumSum(int n, int k);

int main() {
    cout << minimumSum(2, 6);
    return 0;
}

int minimumSum(int n, int k) {
    int arr[n];
    int sum = 0;
    // In the final array, you can have 1, 2, 3... up to floor(k/2)
    for (int i = 1; i <= k/2; i++) {
        arr[i-1] = i;
    }
    // All the other number must be greater than or equal to k
    // There are k/2 "small number" and n - k/2 "big number"
    for (int j = 0; j < n-k/2; j++) {
        arr[k/2 + j] = k + j;
    }
    // Sum of first k/2 number: s = (1 + k/2)/2

    // Sum of "big number": S = (k + (n - k/2))/2

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum;
}