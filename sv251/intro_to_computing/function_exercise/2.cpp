#include <iostream>
using namespace std;

bool isPrime(int n);

int main() {
    cout << "Input array size: ";
    int N, n, count = 0;
    cin >> N;
    int arr[N];
    for (int i = 0; i < N; i++) {
        cout << "Input a number: ";
        cin >> arr[i];
        n = arr[i];
        if (isPrime(n)) count++;
    }
    cout << "There are " << count << " prime numbers." << endl;
}

bool isPrime(int n) {
    if (n==1) return false;
    for (int i = 2; i <= n/2; i++) {
        if (n%i == 0)   return false;
    }
    return true;
}