#include <iostream>
using namespace std;

int main() {
    cout << "Input array size: ";
    int N, n, count = 0;
    cin >> N;
    int arr[N];
    for (int i = 0; i < N; i++) {
        cout << "Input a number: ";
        cin >> arr[i];
        n = arr[i];
        if (n != 1) {
        bool isPrime = true;
        for (int i=2; i<n; i++) {
            if (n%i==0) isPrime = false;
        }
        if (isPrime) count += 1;
        }
    }
    cout << "There are " << count << " prime numbers." << endl;
}