#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n);

int main() {
    int L, R, temp;
    cin >> L >> R;

    if (L > R) {
        temp = L;
        L = R;
        R = temp;
    }

    for (int i = L; i <= R; i++) {
        if (isPrime(i)) cout << i << " ";
    }

    return 0;
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= n/2; i++) {
        if (n%i == 0)   return false;
    }
    return true;
}
